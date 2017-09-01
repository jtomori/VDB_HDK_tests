/*
 * Copyright (c) 2017
 *	Side Effects Software Inc.  All rights reserved.
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
 * This SOP builds a star.
 */

#ifndef __SOP_Star_h__
#define __SOP_Star_h__

#include <SOP/SOP_Node.h>

namespace HDK_Sample {
class SOP_Star : public SOP_Node
{
public:
    static OP_Node		*myConstructor(OP_Network*, const char *,
							    OP_Operator *);

    /// Stores the description of the interface of the SOP in Houdini.
    /// Each parm template refers to a parameter.
    static PRM_Template		 myTemplateList[];


protected:
         SOP_Star(OP_Network *net, const char *name, OP_Operator *op);
    virtual ~SOP_Star();


    /// cookMySop does the actual work of the SOP computing, in this
    /// case, a star shape.
    virtual OP_ERROR		 cookMySop(OP_Context &context);

private:
    /// The following list of accessors simplify evaluating the parameters
    /// of the SOP.
    int		DIVISIONS(fpreal t)	{ return evalInt  ("divs", 0, t); }

    /// Member variables are stored in the actual SOP, not with the geometry
    /// In this case these are just used to transfer data to the local
    /// variable callback.
    /// Another use for local data is a cache to store expensive calculations.
    int		myCurrPoint;
};
} // End HDK_Sample namespace

#endif
