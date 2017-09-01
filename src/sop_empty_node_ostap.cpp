/*
 * Copyright (c) 2017
 *  Side Effects Software Inc.  All rights reserved.
 *
 * Redistribution and use of Houdini Development Kit samples in source and
 * binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. The name of Side Effects Software may not be used to endorse or
 *    promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY SIDE EFFECTS SOFTWARE `AS IS' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 * NO EVENT SHALL SIDE EFFECTS SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *----------------------------------------------------------------------------
 * The Star SOP
 */

#include "sop_empty_node_ostap.h"

#include <GU/GU_Detail.h>
#include <GEO/GEO_PrimPoly.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <CH/CH_LocalVariable.h>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>
#include <SYS/SYS_Math.h>
#include <limits.h>

using namespace HDK_Sample;

//
// Help is stored in a "wiki" style text file.  This text file should be copied
// to $HOUDINI_PATH/help/nodes/sop/star.txt
//
// See the sample_install.sh file for an example.
//


///
/// newSopOperator is the hook that Houdini grabs from this dll
/// and invokes to register the SOP.  In this case we add ourselves
/// to the specified operator table.
///
void
newSopOperator(OP_OperatorTable *table)
{
    table->addOperator(new OP_Operator(
        "hdk_star",                 // Internal name
        "Star",                     // UI name
        SOP_Star::myConstructor,    // How to build the SOP
        SOP_Star::myTemplateList,   // My parameters
        0,                          // Min # of sources
        0,                          // Max # of sources
        OP_FLAG_GENERATOR));        // Flag it as generator
}

static PRM_Name     negativeName("nradius", "Negative Radius");
//                   ^^^^^^^^    ^^^^^^^^^^^^^^^
//                   internal    descriptive version

static PRM_Default  fiveDefault(5);     // Default to 5 divisions
static PRM_Default  radiiDefaults[] = {
               PRM_Default(1),      // Outside radius
               PRM_Default(0.3)     // Inside radius
            };

PRM_Template
SOP_Star::myTemplateList[] = {
    PRM_Template(PRM_INT,           // Integer parameter.
         PRM_Template::PRM_EXPORT_TBX,  // Export to top of viewer
                        // when user selects this node
         1,         // One integer in this row/parameter
         &PRMdivName,   // Name of this parameter - must be static
         &fiveDefault,  // Default for this parameter - ditto
         0,     // Menu for this parameter
         &PRMdivision2Range // Valid range
         ),
    PRM_Template(PRM_XYZ,   2, &PRMradiusName, radiiDefaults),
    PRM_Template(PRM_TOGGLE,    1, &negativeName),
    PRM_Template(PRM_XYZ,       3, &PRMcenterName),
    PRM_Template(PRM_ORD,   1, &PRMorientName, 0, &PRMplaneMenu),
    PRM_Template()
};



OP_Node *
SOP_Star::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
    return new SOP_Star(net, name, op);
}

SOP_Star::SOP_Star(OP_Network *net, const char *name, OP_Operator *op)
    : SOP_Node(net, name, op)
{
    // This SOP always generates fresh geometry, so setting this flag
    // is a bit redundant, but one could change it to check for the old
    // star and only bump relevant data IDs, (P and the primitive list),
    // depending on what parameters changed.
    mySopFlags.setManagesDataIDs(true);


    myCurrPoint = -1; // To prevent garbage values from being returned
}

SOP_Star::~SOP_Star() {}

OP_ERROR
SOP_Star::cookMySop(OP_Context &context)
{

    fpreal now = context.getTime();

    // Since we don't have inputs, we don't need to lock them.

    return error();
}
