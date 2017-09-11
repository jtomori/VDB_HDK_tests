#ifndef __SOP_my_first_node_h__
#define __SOP_my_first_node_h__

#include <SOP/SOP_Node.h>

namespace MyFirstNode {
class SOP_MyFirstNode : public SOP_Node
{
public:
    static OP_Node		*myConstructor(OP_Network*, const char *, OP_Operator *);

    /// Stores the description of the interface of the SOP in Houdini.
    /// Each parm template refers to a parameter.
    static PRM_Template		 myTemplateList[];
    /// This optional data stores the list of local variables.
    static CH_LocalVariable	 myVariables[];

protected:
    SOP_MyFirstNode(OP_Network *net, const char *name, OP_Operator *op);
    virtual ~SOP_MyFirstNode();


    /// cookMySop does the actual work of the SOP computing, in this
    /// case, a star shape.
    virtual OP_ERROR		 cookMySop(OP_Context &context);

private:

};
} // End HDK_Sample namespace

#endif
