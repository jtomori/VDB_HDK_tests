#include "sop_my_first_node.h"

#include <limits.h>
#include <SYS/SYS_Math.h>

#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>

#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>

#include <GU/GU_Detail.h>
#include <GEO/GEO_PrimPoly.h>

#include <PRM/PRM_Include.h>
#include <CH/CH_LocalVariable.h>

using namespace MyFirstNode; // using namespace, by default not necessarry, but if this file was to be included in other files, it would make things more clear

///
/// newSopOperator is the hook that Houdini grabs from this dll
/// and invokes to register the SOP.  In this case we add ourselves
/// to the specified operator table.
///
void newSopOperator(OP_OperatorTable *table) // defining function, which take as an argument a pointer "table" of "OP_OperatorTable" type and does not return anything
{
	table->addOperator(new OP_Operator( 	// now I am modifying a value of a pointer, I am calling a method, that does some stuff (I am not creating a local copy)
		"hdk_MyFirstNode",          		// Internal name
		"MyFirstNode",              		// UI name
		SOP_MyFirstNode::myConstructor,    	// How to build the SOP // name of a function
		SOP_MyFirstNode::myTemplateList,   	// My parameters // name of an array
		0,                          		// Min # of sources
		0, 									// Max # of sources
        SOP_MyFirstNode::myVariables,       // this is required, otherwise it would mess up amount of inputs
		OP_FLAG_GENERATOR)          		// Flag it as generator // maybe some variable defined in a macro
	);
}

static PRM_Name     negativeName("nradius", "Negative Radius"); // creating variable negativeName of a type PRM_Name, static means that it will be available for the whole program duration
//                   ^^^^^^^^    ^^^^^^^^^^^^^^^
//                   internal    descriptive version

static PRM_Default  fiveDefault(5);		// Default to 5 divisions
static PRM_Default  radiiDefaults[] = {
               PRM_Default(1),			// Outside radius
               PRM_Default(0.3)			// Inside radius
		};

PRM_Template SOP_MyFirstNode::myTemplateList[] = { // adding data to an array of type PRM_Template, it was defined in header file (belongs to class SOP_Star)
    PRM_Template(PRM_INT,           	// Integer parameter.
         PRM_Template::PRM_EXPORT_TBX,  // Export to top of viewer when user selects this node
         1,         					// One integer in this row/parameter
         &PRMdivName,   				// Name of this parameter - must be static // adress to this variable is pre-defined in some header file which is inculded at the top
         &fiveDefault,  				// Default for this parameter - ditto // this is an adress to my custom variable
         0,     						// Menu for this parameter
         &PRMdivision2Range 			// Valid range
         ),
    PRM_Template(PRM_XYZ,   2, &PRMradiusName, radiiDefaults),
    PRM_Template(PRM_TOGGLE,    1, &negativeName),
    PRM_Template(PRM_XYZ,       3, &PRMcenterName),
    PRM_Template(PRM_ORD,   1, &PRMorientName, 0, &PRMplaneMenu),
    PRM_Template()
};

// Here's how we define local variables for the SOP, it is empty, but necesarry for not breaking stuff
CH_LocalVariable SOP_MyFirstNode::myVariables[] = {};

OP_Node * SOP_MyFirstNode::myConstructor(OP_Network *net, const char *name, OP_Operator *op) // definition of a function, which returns pointer of type OP_Node, this is a special constructor related to HDK
{
    return new SOP_MyFirstNode(net, name, op);
}

SOP_MyFirstNode::SOP_MyFirstNode(OP_Network *net, const char *name, OP_Operator *op)
    : SOP_Node(net, name, op)
{
    // This SOP always generates fresh geometry, so setting this flag
    // is a bit redundant, but one could change it to check for the old
    // star and only bump relevant data IDs, (P and the primitive list),
    // depending on what parameters changed.
    mySopFlags.setManagesDataIDs(true);
}

SOP_MyFirstNode::~SOP_MyFirstNode() {}

OP_ERROR
SOP_MyFirstNode::cookMySop(OP_Context &context)
{
    return error();
}
