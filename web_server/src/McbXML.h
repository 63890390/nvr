/**
 ****************************************************************************
 * <P> McbXML.h - declaration file for basic XML parser written in ANSI C for
 * portability.
 * It works by using recursion and a node tree for breaking down the elements
 * of an XML document.  </P>
 *
 * @version     V1.0
 *
 * @author      Martyn C Brown
 *
 * @changeHistory  
 *	21st August    	2001	 - 	(V1.0) Creation (MCB)
 ****************************************************************************
 */
	
/*
 ****************************************************************************
 * Include only once
 ****************************************************************************
 */
#ifndef McbXML_Included
#define McbXML_Included
#include <stdlib.h>
#include <string.h>

/*
 ****************************************************************************
 * Include all necessary include files
 ****************************************************************************
 */
//#include <tchar.h>

/*
 ****************************************************************************
 * Some common types for char set portable code
 ****************************************************************************
 */
#ifndef LPCTSTR
	#define LPCTSTR const char *
#endif /* LPCTSTR */

#ifndef LPTSTR
	#define LPTSTR char *
#endif /* LPTSTR */

#ifndef TCHAR
	#define TCHAR char
#endif /* TCHAR */

#ifndef FALSE
	#define FALSE 0
#endif /* FALSE */

#ifndef TRUE	
	#define TRUE 1
#endif /* TRUE

    #define _T(name)    (name)
#define _tcscpy(a,b)    STRCPY(a,b)
#define _tcsstr(a,b)    STRSTR(a,b)
#define _tcschr(a,b)    STRCHR(a,b)
#define _tcslen(a)        STRLEN(a)
#define _tcsnicmp(a,b,c) STRNICMP(a,b,c) */

#define _T(name)    (name)
#define _tcscpy(a,b)    strcpy(a,b)
#define _tcsstr(a,b)    strstr(a,b)
#define _tcschr(a,b)    strchr(a,b)
#define _tcslen(a)        strlen(a)
#define _tcsnicmp      strncmp//˵����strnicmp �����ִ�Сд�Ƚ�
/*
 ****************************************************************************
 * List macros.
 ****************************************************************************
 */

#define ListEntry(ptr,type,member)\
	((type*)((char*)ptr-(unsigned long)(&((type*)0)->member)))

/*
 ****************************************************************************
 * Enumeration used in union to decipher what type a node is.
 ****************************************************************************
 */
 typedef enum McbXMLNodeType
{
	eNodeEmpty = 0,
	eNodeAttribute,	//��ǩ������
	eNodeElement,   //��һ����ǩ�ڵ�
	eNodeText,      //�ڵ������
	eNodeClear      //ע��

} McbXMLNodeType;

#define  McbSTOREOFFSETS

/*
 ****************************************************************************
 * Structure used for a node
 ****************************************************************************
 */
 typedef struct McbXMLNode
{
   /*
    *************************************************************************
    * This dictates what the node is (and consequently which pointer should
	* be used to obtain the appropriate node).
    *************************************************************************
    */
	enum McbXMLNodeType type;//�ڵ�����ԣ������˽ڵ�����

   /*
    *************************************************************************
    * Union to access the appropriate node.
    *************************************************************************
    */
	union
	{
		struct McbXMLAttribute	*pAttrib;  //����
		struct McbXMLElement	*pElement; //��һ���ڵ�
		struct McbXMLText		*pText;    //�ڵ�������ı�
		struct McbXMLClear		*pClear;
        struct McbXMLText		*pCommnetText; //ע�ͣ�gancj
	} node;

#ifdef McbSTOREOFFSETS
	int nStringOffset;
#endif /* McbSTOREOFFSETS */

} McbXMLNode;

/*
 ****************************************************************************
 * Structure used to manage list of nodes
 ****************************************************************************
 */
 typedef struct McbXMLElement
{
	LPTSTR					lpszName;		/* ��ǩ����			 */
	int						nSize;			/* Num of child nodes		 *///�ӽڵ�ĸ���
	int						nMax;			/* Num of allocated nodes	 *///������ڵ�ĸ���
	int						nIsDeclaration;	/* Whether node is an XML	 *///1--��ʾ<?xml ?>������ʽ
											/* declaration - '<?xml ?>'	 *///�Ƿ��ӽڵ���XML��ʽ
	struct McbXMLNode		*pEntries;		/* Array of child nodes		 *///�ӽڵ�����
    /***************************************************************
    * �ýڵ�����˸��׽ڵ�����ݣ�����
    * 
    ***************************************************************/
	struct McbXMLElement		*pParent;		/* Pointer to parent element *///�ýڵ�ĸ��ڵ�
} McbXMLElement;

/*
 ****************************************************************************
 * Structure for XML text
 ****************************************************************************
 */
 typedef struct McbXMLText
{
	LPTSTR lpszValue;

} McbXMLText;

/*
 ****************************************************************************
 * Structure for XML clear (unformatted) node
 ****************************************************************************
 */
 typedef struct McbXMLClear
{
	LPTSTR lpszOpenTag;
	LPTSTR lpszValue;
	LPTSTR lpszCloseTag;

} McbXMLClear;

/*
 ****************************************************************************
 * Structure for XML attribute.
 ****************************************************************************
 */
 typedef struct McbXMLAttribute
{
	LPTSTR lpszName;
	LPTSTR lpszValue;

} McbXMLAttribute;

/*
 ****************************************************************************
 * Enumeration for XML parse errors.
 ****************************************************************************
 */
 typedef enum McbXMLError
{
	eXMLErrorNone = 0,
	eXMLErrorEmpty,
	eXMLErrorFirstNotStartTag,
	eXMLErrorMissingTagName,
	eXMLErrorMissingEndTagName,
	eXMLErrorNoMatchingQuote,
	eXMLErrorUnmatchedEndTag,
	eXMLErrorUnexpectedToken,
	eXMLErrorInvalidTag,
	eXMLErrorNoElements

} McbXMLError;

/*
 ****************************************************************************
 * Structure used to obtain error details if the parse fails.
 ****************************************************************************
 */
 typedef struct McbXMLResults
{
	enum McbXMLError error;
	int				nLine;
	int				nColumn;

} McbXMLResults;

/*
 ****************************************************************************
 * Construct/delete root element
 ****************************************************************************
 */
McbXMLElement * McbCreateRoot();
void McbDeleteRoot(McbXMLElement * pElement);

/*
 ****************************************************************************
 * Obtain error information in a string.
 ****************************************************************************
 */
LPCTSTR McbGetError(McbXMLError error);

/*
 ****************************************************************************
 * Parse XML string into elements.  This returns a pointer to the first 
 * element (created on the heap) if successful.  This must be deleted by 
 * first calling McbDeleteElement() to recursively delete child nodes then 
 * calling free on the element to cleanup the heap.
 * If the function fails then 0 will be returned.  If the results pointer
 * given to the function was not 0 the error, line and column can be 
 * obtained.
 ****************************************************************************
 */
McbXMLElement * McbParseXML(LPCTSTR lpszXML, McbXMLResults *pResults);

/*
 ****************************************************************************
 * Clears an element (deletes its children and the memory which belongs to 
 * it).
 ****************************************************************************
 */
void McbDeleteElement(McbXMLElement *pEntry);

/*
 ****************************************************************************
 * Enumerate nodes in the list returning a pointer to a node.  The index 
 * pointer should be initialised to zero initially - this will be incremented 
 * for each subsequent node that is obtained.
 * 0 will be returned when all nodes have been obtained.
 ****************************************************************************
 */
McbXMLNode * McbEnumNodes(McbXMLElement *pEntry, int *pnIndex);

/*
 ****************************************************************************
 * Recursively search the tree for the required element based on the given
 * path.
 ****************************************************************************
 */
McbXMLElement * McbFindElement(McbXMLElement *pHead, LPCTSTR lpszName);

/*
 ****************************************************************************
 * Search the given element for an attribute.
 ****************************************************************************
 */
McbXMLAttribute * McbFindAttribute(McbXMLElement *pEntry, LPCTSTR lpszAttrib);

/*
 ****************************************************************************
 * Enumerate elements on the given element.
 ****************************************************************************
 */
McbXMLElement * McbEnumElements(McbXMLElement *pEntry, int *pnIndex);

/*
 ****************************************************************************
 * Add an attribute to the element
 ****************************************************************************
 */
McbXMLAttribute * McbAddAttribute(McbXMLElement *pEntry, LPTSTR lpszName, 
	LPTSTR lpszValue, int nGrowBy);

McbXMLText * McbAddText(McbXMLElement *pEntry, LPTSTR lpszValue, int nGrowBy);

/*
 ****************************************************************************
 * Enumerate attributes on the given element.
 ****************************************************************************
 */
McbXMLAttribute * McbEnumAttributes(McbXMLElement *pEntry, int *pnIndex);

/*
 ****************************************************************************
 * Create elements in the list based on the path, returning the final node.
 ****************************************************************************
 */
McbXMLElement * McbCreateElements(McbXMLElement *pEntry, LPCTSTR lpszPath);

/*
 ****************************************************************************
 * Duplicate a string.
 ****************************************************************************
 */
LPTSTR McbStrdup(LPCTSTR lpszData, int cbData);

/*
 ****************************************************************************
 * Create an XML string from the head element.
 * If successful this returns the XML string representation of the specified 
 * XML element node and its subnodes.  This string must be deleted with 
 * free().
 *
 * If the size pointer is not 0 then the total size of the returned string
 * NOT INCLUDING THE NULL TERMINATOR will be updated.
 ****************************************************************************
 */
LPTSTR McbCreateXMLString(McbXMLElement * pHead, int nFormat, int *pnSize);

int McbCreateXMLStringR(McbXMLElement * pEntry, LPTSTR lpszMarker, 
	int nFormat);

/*
 ****************************************************************************
 * Add clear unformatted data to the node.
 ****************************************************************************
 */
McbXMLClear * McbAddCData(McbXMLElement *pEntry, LPTSTR lpszValue, int nGrowBy);


/*
 ****************************************************************************
 * Toby add new functions.
 ****************************************************************************
 */
McbXMLElement* AddElementToXML(McbXMLElement *pParent,LPTSTR lpszText);
McbXMLAttribute* AddAttrToXML(McbXMLElement *pEntry,LPTSTR lpszName,LPTSTR lpszValue);
void DeleteElementFromXML(McbXMLElement *pEntry);
void DeleteAttrFromXML(McbXMLAttribute *pEntry);

//void clearList()

#endif /* McbXML_Included */
