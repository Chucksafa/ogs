/**
 * \file   ElementStatus.cpp
 * \author Karsten Rink
 * \date   2012-12-18
 * \brief  Implementation of the ElementStatus class.
 *
 * \copyright
 * Copyright (c) 2013, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#include "ElementStatus.h"

#include "Mesh.h"
#include "Node.h"
#include "Elements/Element.h"

namespace MeshLib {

ElementStatus::ElementStatus(Mesh const*const mesh)
: _mesh(mesh), _element_status(mesh->getNElements(), true)
{
	const std::vector<MeshLib::Node*> &nodes (_mesh->getNodes());
	for (auto node = nodes.begin(); node != nodes.end(); ++node)
		_active_nodes.push_back((*node)->getNElements());
}


std::vector<unsigned> ElementStatus::getActiveElements() const
{
	std::vector<unsigned> active_elements;
	active_elements.reserve(this->getNActiveElements());
	const std::size_t nElems (_mesh->getNElements());
	for (std::size_t i=0; i<nElems; ++i)
		if (_element_status[i])
			active_elements.push_back(i);
	return active_elements;
}

std::vector<unsigned> ElementStatus::getActiveNodes() const 
{
	std::vector<unsigned> active_nodes;
	active_nodes.reserve(this->getNActiveNodes());
	const std::size_t nNodes (_mesh->getNNodes());
	for (std::size_t i=0; i<nNodes; ++i)
		if (_active_nodes[i]>0)
			active_nodes.push_back(i);
	return active_nodes;
}

unsigned ElementStatus::getNActiveNodes() const 
{
	return _active_nodes.size() - std::count(_active_nodes.begin(), _active_nodes.end(), 0);
}

unsigned ElementStatus::getNActiveElements() const 
{
	return static_cast<unsigned>(std::count(_element_status.begin(), _element_status.end(), true));
}

void ElementStatus::setElementStatus(unsigned i, bool status)
{
	if (_element_status[i] != status)
	{
		const int change = (status) ? 1 : -1;
		_element_status[i] = status;
		const unsigned nElemNodes (_mesh->getElement(i)->getNNodes());
		MeshLib::Node const*const*const nodes = _mesh->getElement(i)->getNodes();
		for (unsigned i=0; i<nElemNodes; ++i)
			_active_nodes[nodes[i]->getID()] += change;
	}
}

}

