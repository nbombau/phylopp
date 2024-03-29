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

#ifndef ICONSENSOR_STRATEGY_H
#define ICONSENSOR_STRATEGY_H

#include "phylopp/Domain/ITreeCollection.h"
#include "phylopp/Consensor/IConsensorObserver.h"
#include "phylopp/Consensor/ClusterTree.h"

namespace Consensus
{
template <class Node, class Observer>
class IConsensorStrategy
{
public:
    virtual Domain::ITree<Node> consensus(Domain::ITreeCollection<Node>& trees, Observer& observer) = 0;
};
}

#endif
