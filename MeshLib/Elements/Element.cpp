/**
 * \file
 * \author Karsten Rink
 * \date   2012-05-02
 * \brief  Implementation of the Element class.
 *
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#include "Element.h"

#include "logog/include/logog.hpp"

#include "MathLib/MathTools.h"
#include "MeshLib/Node.h"

#include "Line.h"

namespace MeshLib {

Element::Element(std::size_t id)
    : _nodes(nullptr), _id(id), _content(-1.0), _neighbors(nullptr)
{
}

Element::~Element()
{
    delete [] this->_nodes;
    delete [] this->_neighbors;
}

void Element::setNeighbor(Element* neighbor, unsigned const face_id)
{
    if (neighbor == this)
        return;

    this->_neighbors[face_id] = neighbor;
}

boost::optional<unsigned> Element::addNeighbor(Element* e)
{
    if (e == this ||
        e == nullptr ||
        e->getDimension() != this->getDimension())
        return boost::optional<unsigned>();

    if (this->hasNeighbor(e))
        return boost::optional<unsigned>();

    Node* face_nodes[3];
    const unsigned nNodes (this->getNBaseNodes());
    const unsigned eNodes (e->getNBaseNodes());
    const Node* const* e_nodes = e->getNodes();
    unsigned count(0);
    const unsigned dim (this->getDimension());
    for (unsigned i(0); i<nNodes; i++)
        for (unsigned j(0); j<eNodes; j++)
            if (_nodes[i] == e_nodes[j])
            {
                face_nodes[count] = _nodes[i];
                // increment shared nodes counter and check if enough nodes are similar to be sure e is a neighbour of this
                if ((++count)>=dim)
                {
                    _neighbors[ this->identifyFace(face_nodes) ] = e;
                    return boost::optional<unsigned>(e->identifyFace(face_nodes));
                }
            }

    return boost::optional<unsigned>();
}

MeshLib::Node Element::getCenterOfGravity() const
{
    const unsigned nNodes (this->getNBaseNodes());
    MeshLib::Node center(0,0,0);
    for (unsigned i=0; i<nNodes; ++i)
    {
        center[0] += (*_nodes[i])[0];
        center[1] += (*_nodes[i])[1];
        center[2] += (*_nodes[i])[2];
    }
    center[0] /= nNodes;
    center[1] /= nNodes;
    center[2] /= nNodes;
    return center;
}

void Element::computeSqrEdgeLengthRange(double &min, double &max) const
{
    min = std::numeric_limits<double>::max();
    max = 0;
    const unsigned nEdges (this->getNEdges());
    for (unsigned i=0; i<nEdges; i++)
    {
        const double dist (MathLib::sqrDist(*getEdgeNode(i,0), *getEdgeNode(i,1)));
        min = (dist<min) ? dist : min;
        max = (dist>max) ? dist : max;
    }
}

void Element::computeSqrNodeDistanceRange(double &min, double &max, bool check_allnodes) const
{
    min = std::numeric_limits<double>::max();
    max = 0;
    const unsigned nnodes = check_allnodes ? getNNodes() : getNBaseNodes();
    for (unsigned i=0; i<nnodes; i++)
    {
        for (unsigned j=i+1; j<nnodes; j++)
        {
            const double dist (MathLib::sqrDist(*getNode(i), *getNode(j)));
            min = std::min(dist, min);
            max = std::max(dist, max);
        }
    }
}

const Element* Element::getNeighbor(unsigned i) const
{
#ifndef NDEBUG
    if (i < getNNeighbors())
#endif
        return _neighbors[i];
#ifndef NDEBUG
    ERR("Error in MeshLib::Element::getNeighbor() - Index does not exist.");
    return nullptr;
#endif
}

unsigned Element::getNodeIDinElement(const MeshLib::Node* node) const
{
    const unsigned nNodes (this->getNBaseNodes());
    for (unsigned i(0); i<nNodes; i++)
        if (node == _nodes[i])
            return i;
    return std::numeric_limits<unsigned>::max();
}

const Node* Element::getNode(unsigned i) const
{
#ifndef NDEBUG
    if (i < getNNodes())
#endif
        return _nodes[i];
#ifndef NDEBUG
    ERR("Error in MeshLib::Element::getNode() - Index %d in %s", i, MeshElemType2String(getGeomType()).c_str());
    return nullptr;
#endif
}

void Element::setNode(unsigned idx, Node* node)
{
#ifndef NDEBUG
    if (idx < getNNodes())
#endif
        _nodes[idx] = node;
}

unsigned Element::getNodeIndex(unsigned i) const
{
#ifndef NDEBUG
    if (i<getNNodes())
#endif
        return _nodes[i]->getID();
#ifndef NDEBUG
    ERR("Error in MeshLib::Element::getNodeIndex() - Index does not exist.");
    return std::numeric_limits<unsigned>::max();
#endif
}

bool Element::hasNeighbor(Element* elem) const
{
    unsigned nNeighbors (this->getNNeighbors());
    for (unsigned i=0; i<nNeighbors; i++)
        if (this->_neighbors[i]==elem)
            return true;
    return false;
}

bool Element::isBoundaryElement() const
{
    return std::any_of(_neighbors, _neighbors + this->getNNeighbors(),
        [](MeshLib::Element const*const e){ return e == nullptr; });
}

#ifndef NDEBUG
std::ostream& operator<<(std::ostream& os, Element const& e)
{
    os << "Element #" << e._id << " @ " << &e << " with " << e.getNNeighbors()
       << " neighbours\n";

    unsigned const nnodes = e.getNNodes();
    MeshLib::Node* const* const nodes = e.getNodes();
    os << "MeshElemType: "
        << static_cast<std::underlying_type<MeshElemType>::type>(e.getGeomType())
        << " with " << nnodes << " nodes: { ";
    for (unsigned n = 0; n < nnodes; ++n)
        os << nodes[n]->getID() << " @ " << nodes[n] << "  ";
    os << "}\n";
    return os;
}
#endif  // NDEBUG

}
