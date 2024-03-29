/*
    Copyright (C) 2011 Emmanuel Teisaire, Nicolás Bombau, Carlos Castro, Damián Domé, FuDePAN

    This file is part of the Phyloloc project.

    Phyloloc is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Phyloloc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Phyloloc.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DUMMY_OBSERVER_H
#define DUMMY_OBSERVER_H

template <class Node>
class DummyObserver //: public Consensus::IConsensorObserver<Node>
{
public:
    DummyObserver()
    {}
    void onStart(const Domain::ITreeCollection<Node>& /*trees*/)
    {}
    void onInclude(Node* /*node*/, const Consensus::bitset& /*cluster*/)
    {}
    void onExclude(Node* /*node*/, const Consensus::bitset& /*cluster*/)
    {}
    void onEnd(Domain::ITree<Node>& /*consensed*/)
    {}
};

#endif
