#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaStackServer/AddressSpaceModel/ObjectNodeClass.h"

using namespace OpcUaStackCore;

namespace OpcUaStackServer
{

	InformationModelAccess::InformationModelAccess(void)
	: informationModel_()
	{
	}

	InformationModelAccess::InformationModelAccess(InformationModel::SPtr informationModel)
	{
		informationModel_ = informationModel;
	}

	InformationModelAccess::~InformationModelAccess(void)
	{
	}

	void
	InformationModelAccess::informationModel(InformationModel::SPtr informationModel)
	{
		informationModel_ = informationModel;
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// node functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	bool
	InformationModelAccess::rootNode(BaseNodeClass::SPtr& baseNodeClass, bool logOnError)
	{
		OpcUaNodeId nodeId;
		nodeId.nodeId(OpcUaId_RootFolder);
		return getNode(nodeId, baseNodeClass, logOnError);
	}

	bool
	InformationModelAccess::getNode(const OpcUaNodeId& nodeId, BaseNodeClass::SPtr& baseNodeClass, bool logOnError)
	{
		baseNodeClass = informationModel_->find(nodeId);
		if (baseNodeClass.get() == nullptr) {
			if (!logOnError) return false;

			Log(Error, "node not found in information model")
				.parameter("NodeId", nodeId);
			return false;
		}
		return true;
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// child functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	bool
	InformationModelAccess::getChild(BaseNodeClass::SPtr baseNodeClass, BaseNodeClass::Vec& childBaseNodeClassVec)
	{
		childBaseNodeClassVec.clear();

		ReferenceItemMultiMap::iterator it;
		for (
			it = baseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
			it != baseNodeClass->referenceItemMap().referenceItemMultiMap().end();
			it++
		)
		{
			ReferenceItem::SPtr referenceItem = it->second;
			if (!referenceItem->isForward_) continue;
			BaseNodeClass::SPtr childBaseNodeClass = informationModel_->find(referenceItem->nodeId_);
			if (childBaseNodeClass.get() == nullptr) {
				Log(Warning, "child node not found in information model")
					.parameter("ParentNodeId", baseNodeClass->getNodeId())
					.parameter("ChildNodeId", referenceItem->nodeId_);
				return false;
			}
			childBaseNodeClassVec.push_back(childBaseNodeClass);
		}
		return true;
	}

	bool
	InformationModelAccess::getChildHierarchically(BaseNodeClass::SPtr baseNodeClass, BaseNodeClass::Vec& childBaseNodeClassVec)
	{
		childBaseNodeClassVec.clear();

		ReferenceItemMultiMap::iterator it;
		for (
			it = baseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
			it != baseNodeClass->referenceItemMap().referenceItemMultiMap().end();
			it++
		)
		{
			ReferenceItem::SPtr referenceItem = it->second;
			if (!referenceItem->isForward_) continue;

			if (!isReferenceHierarchically(it->first)) continue;

			BaseNodeClass::SPtr childBaseNodeClass = informationModel_->find(referenceItem->nodeId_);
			if (childBaseNodeClass.get() == nullptr) {
				Log(Warning, "child node not found in information model")
					.parameter("ParentNodeId", baseNodeClass->getNodeId())
					.parameter("ChildNodeId", referenceItem->nodeId_);
				return false;
			}
			childBaseNodeClassVec.push_back(childBaseNodeClass);
		}
		return true;
	}

	bool
	InformationModelAccess::getChildNonHierarchically(BaseNodeClass::SPtr baseNodeClass, BaseNodeClass::Vec& childBaseNodeClassVec)
	{
		childBaseNodeClassVec.clear();

		ReferenceItemMultiMap::iterator it;
		for (
			it = baseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
			it != baseNodeClass->referenceItemMap().referenceItemMultiMap().end();
			it++
		)
		{
			ReferenceItem::SPtr referenceItem = it->second;
			if (!referenceItem->isForward_) continue;

			if (isReferenceHierarchically(it->first)) continue;

			BaseNodeClass::SPtr childBaseNodeClass = informationModel_->find(referenceItem->nodeId_);
			if (childBaseNodeClass.get() == nullptr) {
				Log(Warning, "child node not found in information model")
					.parameter("ParentNodeId", baseNodeClass->getNodeId())
					.parameter("ChildNodeId", referenceItem->nodeId_);
				return false;
			}
			childBaseNodeClassVec.push_back(childBaseNodeClass);
		}
		return true;
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// parent functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	bool
	InformationModelAccess::getParentReference(BaseNodeClass::SPtr baseNodeClass, std::vector<OpcUaNodeId>& referenceTypeNodeIdVec, ReferenceItem::Vec& referenceItemVec)
	{
		referenceTypeNodeIdVec.clear();
		referenceItemVec.clear();

		ReferenceItemMultiMap::iterator it;
		for (
			it = baseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
			it != baseNodeClass->referenceItemMap().referenceItemMultiMap().end();
			it++
		)
		{
			ReferenceItem::SPtr referenceItem = it->second;
			if (referenceItem->isForward_) continue;
			referenceTypeNodeIdVec.push_back(it->first);
			referenceItemVec.push_back(referenceItem);
		}
		return true;
	}

	bool
	InformationModelAccess::getParent(BaseNodeClass::SPtr baseNodeClass, ReferenceItem::Vec& referenceItemVec)
	{
		referenceItemVec.clear();

		ReferenceItemMultiMap::iterator it;
		for (
			it = baseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
			it != baseNodeClass->referenceItemMap().referenceItemMultiMap().end();
			it++
		)
		{
			ReferenceItem::SPtr referenceItem = it->second;
			if (referenceItem->isForward_) continue;
			referenceItemVec.push_back(referenceItem);
		}
		return true;
	}

	bool
	InformationModelAccess::getParent(BaseNodeClass::SPtr baseNodeClass, std::vector<OpcUaNodeId>& nodeIdVec)
	{
		nodeIdVec.clear();

		ReferenceItemMultiMap::iterator it;
		for (
			it = baseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
			it != baseNodeClass->referenceItemMap().referenceItemMultiMap().end();
			it++
		)
		{
			ReferenceItem::SPtr referenceItem = it->second;
			if (referenceItem->isForward_) continue;
			nodeIdVec.push_back(referenceItem->nodeId_);
		}
		return true;
	}

	bool
	InformationModelAccess::getParent(BaseNodeClass::SPtr baseNodeClass, BaseNodeClass::Vec& childBaseNodeClassVec)
	{
		childBaseNodeClassVec.clear();

		ReferenceItemMultiMap::iterator it;
		for (
			it = baseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
			it != baseNodeClass->referenceItemMap().referenceItemMultiMap().end();
			it++
		)
		{
			ReferenceItem::SPtr referenceItem = it->second;
			if (referenceItem->isForward_) continue;
			BaseNodeClass::SPtr childBaseNodeClass = informationModel_->find(referenceItem->nodeId_);
			if (childBaseNodeClass.get() == nullptr) {
				Log(Warning, "parent node not found in information model")
					.parameter("ChildNodeId", baseNodeClass->getNodeId())
					.parameter("ParentNodeId", referenceItem->nodeId_);
				return false;
			}
			childBaseNodeClassVec.push_back(childBaseNodeClass);
		}
		return true;
	}

	bool
	InformationModelAccess::getParentHierarchically(BaseNodeClass::SPtr baseNodeClass, BaseNodeClass::Vec& childBaseNodeClassVec)
	{
		childBaseNodeClassVec.clear();

		ReferenceItemMultiMap::iterator it;
		for (
			it = baseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
			it != baseNodeClass->referenceItemMap().referenceItemMultiMap().end();
			it++
		)
		{
			ReferenceItem::SPtr referenceItem = it->second;
			if (referenceItem->isForward_) continue;

			if (!isReferenceHierarchically(it->first)) continue;

			BaseNodeClass::SPtr childBaseNodeClass = informationModel_->find(referenceItem->nodeId_);
			if (childBaseNodeClass.get() == nullptr) {
				Log(Warning, "parent node not found in information model")
					.parameter("ChildNodeId", baseNodeClass->getNodeId())
					.parameter("ParentNodeId", referenceItem->nodeId_);
				return false;
			}
			childBaseNodeClassVec.push_back(childBaseNodeClass);
		}
		return true;
	}

	bool
	InformationModelAccess::getParentHierarchically(BaseNodeClass::SPtr baseNodeClass, std::vector<OpcUaNodeId>& nodeIdVec)
	{
		nodeIdVec.clear();

		ReferenceItemMultiMap::iterator it;
		for (
			it = baseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
			it != baseNodeClass->referenceItemMap().referenceItemMultiMap().end();
			it++
		)
		{
			ReferenceItem::SPtr referenceItem = it->second;
			if (referenceItem->isForward_) continue;

			if (!isReferenceHierarchically(it->first)) continue;

			nodeIdVec.push_back(referenceItem->nodeId_);
		}
		return true;
	}

	bool
	InformationModelAccess::getParentNonHierarchically(BaseNodeClass::SPtr baseNodeClass, BaseNodeClass::Vec& childBaseNodeClassVec)
	{
		childBaseNodeClassVec.clear();

		ReferenceItemMultiMap::iterator it;
		for (
			it = baseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
			it != baseNodeClass->referenceItemMap().referenceItemMultiMap().end();
			it++
		)
		{
			ReferenceItem::SPtr referenceItem = it->second;
			if (referenceItem->isForward_) continue;

			if (isReferenceHierarchically(it->first)) continue;

			BaseNodeClass::SPtr childBaseNodeClass = informationModel_->find(referenceItem->nodeId_);
			if (childBaseNodeClass.get() == nullptr) {
				Log(Warning, "parent node not found in information model")
					.parameter("ChildNodeId", baseNodeClass->getNodeId())
					.parameter("ParentNodeId", referenceItem->nodeId_);
				return false;
			}
			childBaseNodeClassVec.push_back(childBaseNodeClass);
		}
		return true;
	}

	bool
	InformationModelAccess::getParentNonHierarchically(BaseNodeClass::SPtr baseNodeClass, std::vector<OpcUaNodeId>& nodeIdVec)
	{
		nodeIdVec.clear();

		ReferenceItemMultiMap::iterator it;
		for (
			it = baseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
			it != baseNodeClass->referenceItemMap().referenceItemMultiMap().end();
			it++
		)
		{
			ReferenceItem::SPtr referenceItem = it->second;
			if (referenceItem->isForward_) continue;

			if (isReferenceHierarchically(it->first)) continue;

			nodeIdVec.push_back(referenceItem->nodeId_);
		}
		return true;
	}

	BaseNodeClass::SPtr
	InformationModelAccess::getSurrogateParentNode(void)
	{
		OpcUaNodeId nodeId;
		nodeId.set("SurrogateParent");
		return getSurrogateParentNode(nodeId);
	}

	BaseNodeClass::SPtr
	InformationModelAccess::getSurrogateParentNode(OpcUaNodeId& nodeId)
	{
		BaseNodeClass::SPtr baseNodeClass;
		BaseNodeClass::SPtr baseNodeClass0;
		OpcUaNodeId nodeId0;

		nodeId0.set(OpcUaId_ObjectsFolder);
		baseNodeClass0 = informationModel_->find(nodeId0);
		if (baseNodeClass0.get() == nullptr) {
			Log(Error, "objects folder not found in information model");
			return baseNodeClass;
		}

		// get surrogate parent form information model
		baseNodeClass = informationModel_->find(nodeId);
		if (baseNodeClass.get() != nullptr) {
			return baseNodeClass;
		}

		// surrogate parent does not exist. Create a surrogate parent
		baseNodeClass = ObjectNodeClass::construct();
		baseNodeClass->setNodeId(nodeId);
		OpcUaQualifiedName browseName("SurrogateParent");
		baseNodeClass->setBrowseName(browseName);
		OpcUaLocalizedText displayName("en", "SurrogateParent");
		baseNodeClass->setDisplayName(displayName);
		OpcUaLocalizedText description("en", "surrogate parent node");
		baseNodeClass->setDescription(description);
		informationModel_->insert(baseNodeClass);

		// add type reference
		OpcUaNodeId typeNodeId;
		typeNodeId.set(OpcUaId_TypesFolder);
		baseNodeClass->referenceItemMap().add(ReferenceType_HasTypeDefinition, true, typeNodeId);

		// add reference between surrogate node and namespace 0
		baseNodeClass->referenceItemMap().add(ReferenceType_HasComponent, false, nodeId0);
		baseNodeClass0->referenceItemMap().add(ReferenceType_HasComponent, true, *baseNodeClass->getNodeId());

		return baseNodeClass;
	}

	bool
	InformationModelAccess::parentChange(BaseNodeClass::SPtr baseNodeClass, const OpcUaNodeId& oldParentNodeId, const OpcUaNodeId& newParentNodeId)
	{
		bool success;
		ReferenceItemMultiMap::iterator it;
		OpcUaNodeId nodeId = *baseNodeClass->getNodeId();

		// get old parent base node class
		BaseNodeClass::SPtr oldParentBaseNodeClass;
		if (!getNode(oldParentNodeId, oldParentBaseNodeClass)) {
			Log(Error, "cannot change parent, because old parent not found")
				.parameter("NodeId", *baseNodeClass->getNodeId())
				.parameter("OldParentNodeId", oldParentNodeId)
				.parameter("NewParentNodeId", newParentNodeId);
			return false;
		}

		// get new parent base node class
		BaseNodeClass::SPtr newParentBaseNodeClass;
		if (!getNode(newParentNodeId, newParentBaseNodeClass)) {
			Log(Error, "cannot change parent, because new parent not found")
				.parameter("NodeId", *baseNodeClass->getNodeId())
				.parameter("OldParentNodeId", oldParentNodeId)
				.parameter("NewParentNodeId", newParentNodeId);
			return false;
		}

		// remove reference from parent to node
		success = false;
		for (
			it = oldParentBaseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
			it != oldParentBaseNodeClass->referenceItemMap().referenceItemMultiMap().end();
			it++
		) {
			ReferenceItem::SPtr referenceItem = it->second;
			if (referenceItem->nodeId_ == nodeId && referenceItem->isForward_ == true)
			{
				success = true;
				oldParentBaseNodeClass->referenceItemMap().referenceItemMultiMap().erase(it);
				break;
			}
		}
		if (!success) {
			Log(Error, "cannot change parent, because reference from parent to node not found")
				.parameter("NodeId", *baseNodeClass->getNodeId())
				.parameter("OldParentNodeId", oldParentNodeId)
				.parameter("NewParentNodeId", newParentNodeId);
			return false;
		}

		// change reference from node to parent
		success = false;
		for (
			it = baseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
			it != baseNodeClass->referenceItemMap().referenceItemMultiMap().end();
			it++
		) {
			ReferenceItem::SPtr referenceItem = it->second;
			if (referenceItem->nodeId_ == oldParentNodeId && referenceItem->isForward_ == false)
			{
				success = true;
				referenceItem->nodeId_ = newParentNodeId;
				break;
			}
		}
		if (!success) {
			Log(Warning, "cannot change parent, because reference from node to parent not found")
				.parameter("NodeId", *baseNodeClass->getNodeId())
				.parameter("OldParentNodeId", oldParentNodeId)
				.parameter("NewParentNodeId", newParentNodeId);
		}

		// add reference from new parent to node
		newParentBaseNodeClass->referenceItemMap().add(ReferenceType_HasComponent, true, nodeId);
		return true;
	}


	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// reference functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	bool
	InformationModelAccess::isReferenceHierarchically0(const OpcUaNodeId& referenceNodeId)
	{
		if (referenceNodeId.nodeIdType() != OpcUaBuildInType_OpcUaUInt32) {
			Log(Error, "found reference with invalid node id type")
				.parameter("ExpectedNodeIdType", "UINT32")
				.parameter("ActualNodeIdType", referenceNodeId.nodeIdType())
				.parameter("NodeId", referenceNodeId);
			return false;
		}

		uint32_t id = referenceNodeId.nodeId<uint32_t>();
		switch (id)
		{
			case OpcUaId_HierarchicalReferences:
			case OpcUaId_HasEventSource:
			case OpcUaId_HasChild:
			case OpcUaId_Organizes:
			case OpcUaId_HasNotifier:
			case OpcUaId_Aggregates:
			case OpcUaId_HasSubtype:
			case OpcUaId_HasProperty:
			case OpcUaId_HasComponent:
			case OpcUaId_HasOrderedComponent:
				return true;
		}
		return false;
	}

	bool
	InformationModelAccess::isReferenceHierarchically(BaseNodeClass::SPtr referenceBaseNodeClass)
	{
		boost::optional<OpcUaNodeId&> referenceNodeId = referenceBaseNodeClass->getNodeId();
		if (!referenceNodeId) return false;

		if (referenceNodeId->namespaceIndex() == 0) {
			return isReferenceHierarchically0(*referenceNodeId);
		}

		BaseNodeClass::SPtr subTypeBaseNodeClass;
		if (!getSubType(referenceBaseNodeClass, subTypeBaseNodeClass)) return false;
		return isReferenceHierarchically(subTypeBaseNodeClass);
	}

	bool
	InformationModelAccess::isReferenceHierarchically(const OpcUaNodeId& referenceNodeId)
	{
		if (referenceNodeId.namespaceIndex() == 0) {
			return isReferenceHierarchically0(referenceNodeId);
		}

		BaseNodeClass::SPtr referenceBaseNodeClass;
		if (!getNode(referenceNodeId, referenceBaseNodeClass)) return false;
		return isReferenceHierarchically(referenceBaseNodeClass);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// type functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	bool
	InformationModelAccess::getType(BaseNodeClass::SPtr baseNodeClass, BaseNodeClass::SPtr& typeBaseNodeClass)
	{
		std::pair<ReferenceItemMultiMap::iterator,ReferenceItemMultiMap::iterator> it;
		it = baseNodeClass->referenceItemMap().referenceItemMultiMap().equal_range(*ReferenceTypeMap::hasTypeDefinitionTypeNodeId());
		if (it.first == it.second) {
			Log(Warning, "HasTypeDefinition reference not exist in node")
				.parameter("NodeId", baseNodeClass->nodeId());
			return false;
		}

		ReferenceItemMultiMap::iterator itl;
		for (itl = it.first; itl != it.second; itl++) {
			ReferenceItem::SPtr referenceItem  = itl->second;

			if (!referenceItem->isForward_) continue;

			typeBaseNodeClass = informationModel_->find(referenceItem->nodeId_);
			if (typeBaseNodeClass.get() == nullptr) {
				Log(Warning, "type node not found in information model")
					.parameter("SourceNode", "")
					.parameter("TypeNode", "");
				return false;
			}
		}

		Log(Warning, "HasTypeDefinition forward reference not exist in node")
			.parameter("NodeId", baseNodeClass->nodeId());

		return true;
	}

	bool
	InformationModelAccess::getType(BaseNodeClass::SPtr baseNodeClass, OpcUaNodeId& typeNodeId)
	{
		std::pair<ReferenceItemMultiMap::iterator,ReferenceItemMultiMap::iterator> it;
		it = baseNodeClass->referenceItemMap().referenceItemMultiMap().equal_range(*ReferenceTypeMap::hasTypeDefinitionTypeNodeId());
		if (it.first == it.second) {
			Log(Warning, "HasTypeDefinition reference not exist in node")
				.parameter("NodeId", baseNodeClass->nodeId());
			return false;
		}

		ReferenceItemMultiMap::iterator itl;
		for (itl = it.first; itl != it.second; itl++) {
			ReferenceItem::SPtr referenceItem  = itl->second;

			if (!referenceItem->isForward_) continue;
			referenceItem->nodeId_.copyTo(typeNodeId);
			return true;
		}

		Log(Warning, "HasTypeDefinition forward reference not exist in node")
			.parameter("NodeId", baseNodeClass->nodeId());

		return true;
	}

	bool
	InformationModelAccess::getSubType(BaseNodeClass::SPtr baseNodeClass, BaseNodeClass::SPtr& subTypeBaseNodeClass)
	{
		std::pair<ReferenceItemMultiMap::iterator,ReferenceItemMultiMap::iterator> it;
		it = baseNodeClass->referenceItemMap().referenceItemMultiMap().equal_range(*ReferenceTypeMap::hasSubtypeTypeNodeId());
		if (it.first == it.second) {
			Log(Warning, "HasSubTypeDefinition reference not exist in node")
				.parameter("NodeId", baseNodeClass->nodeId());
			return false;
		}

		ReferenceItemMultiMap::iterator itl;
		for (itl = it.first; itl != it.second; itl++) {
			ReferenceItem::SPtr referenceItem  = itl->second;

			if (referenceItem->isForward_) continue;

			subTypeBaseNodeClass = informationModel_->find(referenceItem->nodeId_);
			if (subTypeBaseNodeClass.get() == nullptr) {
				Log(Warning, "sub type node not found in information model")
					.parameter("SourceNode", "")
					.parameter("SubTypeNode", "");
				return false;
			}
		}

		Log(Warning, "HasSubTypeDefinition backward reference not exist in node")
			.parameter("NodeId", baseNodeClass->nodeId());

		return true;
	}

	bool
	InformationModelAccess::getSubType(BaseNodeClass::SPtr baseNodeClass, OpcUaNodeId& subTypeNodeId)
	{
		std::pair<ReferenceItemMultiMap::iterator,ReferenceItemMultiMap::iterator> it;
		it = baseNodeClass->referenceItemMap().referenceItemMultiMap().equal_range(*ReferenceTypeMap::hasSubtypeTypeNodeId());
		if (it.first == it.second) {
			Log(Warning, "HasSubTypeDefinition reference not exist in node")
				.parameter("NodeId", baseNodeClass->nodeId());
			return false;
		}

		ReferenceItemMultiMap::iterator itl;
		for (itl = it.first; itl != it.second; itl++) {
			ReferenceItem::SPtr referenceItem  = itl->second;

			if (referenceItem->isForward_) continue;
			referenceItem->nodeId_.copyTo(subTypeNodeId);
			return true;
		}

		Log(Warning, "HasSubTypeDefinition backward reference not exist in node")
			.parameter("NodeId", baseNodeClass->nodeId());
		return true;
	}


	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// merge function
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	bool
	InformationModelAccess::add(InformationModel::SPtr informationModel, uint16_t namespaceIndex, MergeIf* mergeIf, uint32_t step)
	{
		BaseNodeClass::Vec baseNodeClassVec;

		bool success = true;
		uint32_t actCount = 0;
		uint32_t maxCount = informationModel->informationModelMap().size();

		// clone node classes and insert them into target information model
		InformationModelMap::iterator it1;
		for (
			it1 = informationModel->informationModelMap().begin();
			it1 != informationModel->informationModelMap().end();
			it1++
		) {
			if (mergeIf != NULL && actCount % step == 0) mergeIf->handleMerge(maxCount, actCount);
			actCount++;

			if (namespaceIndex != it1->first.namespaceIndex()) continue;
			BaseNodeClass::SPtr baseNodeClass = it1->second->clone();
			if (!baseNodeClass->getNodeId()) {
				Log(Error, "node contains no node id");
				success = false;
				continue;
			}

			if (!informationModel_->insert(baseNodeClass)) {
				Log(Error, "node id already exist in information model")
					.parameter("NodeId", *baseNodeClass->getNodeId());
				success = false;
				continue;
			}

			baseNodeClassVec.push_back(baseNodeClass);
		}

		// check if there is a target for all references
		BaseNodeClass::Vec::iterator it2;
		for (it2 = baseNodeClassVec.begin(); it2 != baseNodeClassVec.end(); it2++) {
			BaseNodeClass::SPtr baseNodeClass = *it2;

			if (mergeIf != NULL && actCount % step == 0) mergeIf->handleMerge(maxCount*2, actCount+maxCount);
			actCount++;

			// get parent references
			std::vector<OpcUaNodeId> referenceTypeNodeIdVec;
			ReferenceItem::Vec referenceItemVec;
			bool success = getParentReference(baseNodeClass, referenceTypeNodeIdVec, referenceItemVec);
			if (!success || referenceItemVec.size() == 0) {
				Log(Debug, "no parent reference available")
					.parameter("NodeId", *baseNodeClass->getNodeId());
				success = false;
				continue;
			}

			// check all parent references
			for (uint32_t pos = 0; pos < referenceItemVec.size(); pos++) {
				OpcUaNodeId referenceTypeNodeId = referenceTypeNodeIdVec[pos];
				ReferenceItem::SPtr referenceItem = referenceItemVec[pos];

				BaseNodeClass::SPtr parentBaseNodeClass = informationModel_->find(referenceItem->nodeId_);
				if (parentBaseNodeClass.get() != nullptr) continue;

				// parent node not exist
				OpcUaNodeId surrogateParentNodeId;
				OpcUaNodeId::Opt baseNodeClassNodeId = baseNodeClass->getNodeId();
				surrogateParentNodeId.set("SurrogateParent", baseNodeClassNodeId->namespaceIndex());
				BaseNodeClass::SPtr surrogateParentNode = getSurrogateParentNode(surrogateParentNodeId);
				if (surrogateParentNode.get() == nullptr) {
					continue;
				}

				// parent node does not exist. Remove reference
				baseNodeClass->referenceItemMap().remove(referenceTypeNodeId, referenceItem);

				// add reference between node and new parent
				referenceItem = ReferenceItem::construct(true, *baseNodeClass->getNodeId());
				surrogateParentNode->referenceItemMap().add(ReferenceType_HasComponent, referenceItem);

				referenceItem = ReferenceItem::construct(false, *surrogateParentNode->getNodeId());
				baseNodeClass->referenceItemMap().add(ReferenceType_HasComponent, referenceItem);
			}
		}

		return success;
	}

	bool
	InformationModelAccess::containsNodeIds(InformationModel::SPtr informationModel, uint16_t namespaceIndex)
	{
		InformationModelMap::iterator it;
		for (
			it = informationModel->informationModelMap().begin();
			it != informationModel->informationModelMap().end();
			it++
		) {
			BaseNodeClass::SPtr baseNodeClass;
			OpcUaNodeId nodeId = it->first;
			if (nodeId.namespaceIndex() != namespaceIndex) continue;
			if (!getNode(nodeId, baseNodeClass, false)) return false;
		}
		return true;
	}

	bool
	InformationModelAccess::remove(OpcUaNodeId& nodeId)
	{
		InformationModelMap::iterator it1;
		for (
			it1 = informationModel_->informationModelMap().begin();
			it1 != informationModel_->informationModelMap().end();
			it1++
		) {
			BaseNodeClass::SPtr baseNodeClass = it1->second;
			ReferenceItemMultiMap::iterator it2;
			for (
				it2 = baseNodeClass->referenceItemMap().referenceItemMultiMap().begin();
				it2 != baseNodeClass->referenceItemMap().referenceItemMultiMap().end();
				it2++
			) {
				ReferenceItem::SPtr referenceItem = it2->second;
				if (referenceItem->nodeId_ == nodeId) {
					baseNodeClass->referenceItemMap().referenceItemMultiMap().erase(it2);
				}
			}
		}
		informationModel_->remove(nodeId);
		return true;
	}

	bool
	InformationModelAccess::remove(BaseNodeClass::SPtr baseNodeClass)
	{
		return remove(*baseNodeClass->getNodeId());
	}

}

