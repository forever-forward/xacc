/*******************************************************************************
 * Copyright (c) 2017 UT-Battelle, LLC.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompanies this
 * distribution. The Eclipse Public License is available at
 * http://www.eclipse.org/legal/epl-v10.html and the Eclipse Distribution
 * License is available at https://eclipse.org/org/documents/edl-v10.php
 *
 * Contributors:
 *   Alexander J. McCaskey - initial API and implementation
 *******************************************************************************/
#ifndef QUANTUM_IRTOGRAPHVISITOR_HPP_
#define QUANTUM_IRTOGRAPHVISITOR_HPP_

#include "AllGateVisitor.hpp"
#include "Graph.hpp"
#include "xacc.hpp"

namespace xacc {
namespace quantum {

using CircuitNode = HeterogeneousMap;//std::map<std::string, InstructionParameter>;

class IRToGraphVisitor : public AllGateVisitor {

protected:
  std::shared_ptr<Graph> graph;

  std::map<int, CircuitNode> qubitToLastNode;

  int id = 0;

  void addSingleQubitGate(Gate &inst);
  void addTwoQubitGate(Gate &inst);

public:
  IRToGraphVisitor(const int nQubits);
  std::shared_ptr<Graph> getGraph();

  void visit(Hadamard &h) { addSingleQubitGate(h); }

  void visit(Identity &i) { addSingleQubitGate(i);}

  void visit(CZ &cz) { addTwoQubitGate(cz); }

  void visit(CNOT &cn) { addTwoQubitGate(cn); }

  void visit(X &x) { addSingleQubitGate(x); }

  void visit(Y &y) { addSingleQubitGate(y); }

  void visit(Z &z) { addSingleQubitGate(z); }

  void visit(Measure &m) { addSingleQubitGate(m); }

//   void visit(ConditionalFunction &c) {
    // nothing
//   }

  void visit(Rx &rx) { addSingleQubitGate(rx); }

  void visit(Ry &ry) { addSingleQubitGate(ry); }

  void visit(Rz &rz) { addSingleQubitGate(rz); }

  void visit(CPhase &cp) { addTwoQubitGate(cp); }

  void visit(Swap &s) { addTwoQubitGate(s); }

  void visit(U &u) { addSingleQubitGate(u); }
  
  // Base gate visitor, i.e. none of the concrete gates can match.
  // We need to assert here because we cannot generate a graph when there are unknown gates.
  // e.g. there is an 1-1 mapping between node Id (in the graph) and instruction counter (in the circuit),
  // hence, we must fail the graph generation when we encounter an unknown gate.
  void visit(Gate &gate) { xacc::error("Unknown gate '" + gate.name() + "' encountered while processing input circuit. Please provide the IRToGraph implementation for this gate.");}

  virtual ~IRToGraphVisitor() {}
};
} // namespace quantum
} // namespace xacc

#endif
