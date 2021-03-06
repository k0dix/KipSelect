#include "utils/xml.h"

//XPATHRESULT :: CLASS
unsigned int XPATHRESULT::getNodeCount() {
	return xPathObjPtr->nodesetval->nodeNr;
}

xmlNodePtr *XPATHRESULT::getNodePtr() {
	return xPathObjPtr->nodesetval->nodeTab;
}

XPATHRESULT::XPATHRESULT(xmlDocPtr xmlDoc, xmlXPathObjectPtr xPathObjPtr) {
	this->xPathObjPtr = xPathObjPtr;
	this->xmlDoc = xmlDoc;
}

XPATHRESULT::~XPATHRESULT() {
	xmlXPathFreeObject(xPathObjPtr);
}
//XPATHRESULT :: END
//XML :: CLASS
XPATHRESULT XML::evalXPathExp(bool *success, const char *exp) {
	xmlXPathContextPtr context;
	xmlXPathObjectPtr result;
	context = xmlXPathNewContext(xmlDoc);
	if (context == NULL) {
		printf("XML -- Error Makeing New XPath Context\n");
		*success = false;
		return XPATHRESULT();
	}
	result = xmlXPathEvalExpression((xmlChar*) exp, context);
	xmlXPathFreeContext(context);
	if (result == NULL) {
		printf("XML -- Error Evaluating XPath Expression\n");
		*success = false;
		return XPATHRESULT();
	}
	if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
		xmlXPathFreeObject(result);
		printf("XML -- XPath Expression Returned No Results\n");
		*success = false;
		return XPATHRESULT();
	}
	*success = true;
	return XPATHRESULT(xmlDoc, result);
}

XPATHRESULT XML::evalXPathExpFromNode(bool *success, xmlNodePtr nodePtr, const char *exp) {
	xmlXPathContextPtr context;
	xmlXPathObjectPtr result;
	context = xmlXPathNewContext(xmlDoc);
	context->node = nodePtr;
	if (context == NULL) {
		printf("XML -- Error Makeing New XPath Context\n");
		*success = false;
		return XPATHRESULT();
	}
	result = xmlXPathEvalExpression((xmlChar*)exp, context);
	xmlXPathFreeContext(context);
	if (result == NULL) {
		printf("XML -- Error Evaluating XPath Expression\n");
		*success = false;
		return XPATHRESULT();
	}
	if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
		xmlXPathFreeObject(result);
		printf("XML -- XPath Expression Returned No Results\n");
		*success = false;
		return XPATHRESULT();
	}
	*success = true;
	return XPATHRESULT(xmlDoc, result);
}

std::string XML::getKeyword(xmlNodePtr nodePtr) {
	xmlChar *keyword;
	keyword = xmlNodeListGetString(xmlDoc, nodePtr->children, 1);
	std::string out = XMLCHAR_TO_CONSTCHAR(keyword);
	xmlFree(keyword);
	return out;
}

XML::XML(bool *success, const char *xmlFilePath) {
	xmlDoc = xmlParseFile(xmlFilePath);
	if (xmlDoc == NULL) {
		printf("XML -- Failed To Parse Xml File\n");
		*success = false;
		return;
	}
	xmlCur = xmlDocGetRootElement(xmlDoc);
	if (xmlCur == NULL) {
		printf("XML -- Xml File Is Empty\n");
		*success = false;
		return;
	}
	*success = true;
}

XML::~XML() {
	xmlFreeDoc(xmlDoc);
}
//XML :: END