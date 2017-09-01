/*
 *
 * 		Empty SOP Node for Houdini
 * 			   www.kamid.net
 *
 * Original Author: Dave Kin
 * Modified by: Deborah R. Fowler
 * Dec 13, 2012

 * changed name of node and files
 * added a parameter "curious" for demo purposes
 * added version print statement
 
 * Further modified by Deborah R. Fowler
 * Feb 27, 2014 to update to H13.0.237
 */


// Include Standard C Package
//#include <stdio.h>
//#include <stdlib.h>
//using namespace std;

// Include Houdini (HDK) Package
// If you have errors below, make sure to add the "houdini_installation_folder / devkit / include" path
// to your project properties

#include <limits.h>
#include <SYS/SYS_Math.h>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>
#include <GU/GU_Detail.h>
#include <GU/GU_PrimPoly.h>
#include <CH/CH_LocalVariable.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>

#include "sopEmptyNode.h"

using namespace HDK_Sample;


///
/// newSopOperator is the hook that Houdini grabs from this dll
/// and invokes to register the SOP.  In this case we add ourselves
/// to the specified operator table.
///
void
newSopOperator(OP_OperatorTable *table)
{
    table->addOperator(		new OP_Operator("EmptyNode",                		// Node Name - Default Name
                            				"EmptyNodeHDK",            			// UI name
                            				sopEmptyNode::myConstructor,  	// How to build the SOP
                            				sopEmptyNode::myTemplateList,  	// My UI parameters
                            				0,                         			// Min # of I/O sources
                            				0,                         			// Max # of I/O sources
                            				sopEmptyNode::myVariables,     	// Local variables
                            				OP_FLAG_GENERATOR)        		 	// Flag it as generator
    );
};



// This is the parameters for the UI and input variables for the Node...
static PRM_Name         variable_name("curious", "Curious");
static PRM_Default      variable_defaults(0);
static PRM_Range		variable_range(PRM_RANGE_RESTRICTED, 0, PRM_RANGE_UI, 100);

PRM_Template 
sopEmptyNode::myTemplateList[] = {	
		PRM_Template( PRM_FLT, 
		PRM_Template::PRM_EXPORT_TBX,	// Export to top of viewer
						// when user selects this node		
		1, 
		&variable_name, 	
		&variable_defaults,	
		0,	
		&variable_range ),								
		PRM_Template()
};



// Here's how we define local variables for the SOP.
enum {
	VAR_PT,		// Point number $PT
	VAR_NPT		// Number of points $NPT
};

CH_LocalVariable
sopEmptyNode::myVariables[] = {
    { "PT",	VAR_PT, 0 },		// The table provides a mapping
    { "NPT",	VAR_NPT, 0 },	// from text string to integer token
    { 0, 0, 0 },
};

bool
sopEmptyNode::evalVariableValue(fpreal &val, int index, int thread)
{
    // myCurrPoint will be negative when we're not cooking so only try to
    // handle the local variables when we have a valid myCurrPoint index.
    if (myCurrPoint >= 0)
    {
	// Note that "gdp" may be null here, so we do the safe thing
	// and cache values we are interested in.
	switch (index)
	{
	    case VAR_PT:
		val = (fpreal) myCurrPoint;
		return true;
	    case VAR_NPT:
		val = (fpreal) myTotalPoints;
		return true;
	    default:
		/* do nothing */;
	}
    }
    // Not one of our variables, must delegate to the base class.
    return SOP_Node::evalVariableValue(val, index, thread);
}




// These are the constructors...

OP_Node *
sopEmptyNode::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
    return new sopEmptyNode(net, name, op);
}

sopEmptyNode::sopEmptyNode(OP_Network *net, const char *name, OP_Operator *op)
	: SOP_Node(net, name, op)
{
    myCurrPoint = -1;	// To prevent garbage values from being returned
}

sopEmptyNode::~sopEmptyNode()
{
};


// This is what COOKs the SOP
OP_ERROR sopEmptyNode::cookMySop(OP_Context &context)
{

	// First grab the frame time and variables form the UI
    double              now;
    float               variable;
    UT_Interrupt        *boss;

    now 				= context.getTime();
	variable 			= evalFloat  ("curious", 0, now);
	//cout << "Test Message: Version 1 for H13";
	//cout.flush(); // not required on Windows, but usually needed on Linux

	gdp->clearAndDestroy();

    // Check to see that there hasn't been a critical error in cooking the SOP.
    if (error() < UT_ERROR_ABORT)
    {
        boss = UTgetInterrupt();

        if (boss->opStart("Cooking SOP..."))
        {
        	// Remember that there needs to be a command here even if it is an empty node
        	myTotalPoints = myCurrPoint = variable;
        }
        boss->opEnd();
    };

    myCurrPoint = -1;
    return error();
};




