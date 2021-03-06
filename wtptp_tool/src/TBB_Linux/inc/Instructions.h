/******************************************************************************
 *
 *  (C)Copyright 2005 - 2013 Marvell. All Rights Reserved.
 *  
 *  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF MARVELL.
 *  The copyright notice above does not evidence any actual or intended 
 *  publication of such source code.
 *  This Module contains Proprietary Information of Marvell and should be
 *  treated as Confidential.
 *  The information in this file is provided for the exclusive use of the 
 *  licensees of Marvell.
 *  Such users have the right to use, modify, and incorporate this code into 
 *  products for purposes authorized by the license agreement provided they 
 *  include this notice and the associated copyright notice with any such
 *  product. 
 *  The information in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/
 /********************************************************************************
Marvell BSD License Option

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File under the following licensing terms.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.

	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.

	* Neither the name of Marvell nor the names of its contributors may be
	  used to endorse or promote products derived from this software without
	  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/

#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "ErdBase.h"
#include <cstring>

const int MAX_INST_PARAMS = 5;

class CInstruction: public CTimLib {
public:
	CInstruction();
	CInstruction(INSTRUCTION_OP_CODE_SPEC_T eOpCode,
			const string sInstructionName, unsigned int uiNumParamsUsed,
			const string sParam0Name, const string sParam1Name,
			const string sParam2Name, const string sParam3Name,
			const string sParam4Name);
	virtual ~CInstruction(void);

	// copy constructor
	CInstruction(const CInstruction& rhs);
	// assignment operator
	CInstruction& operator=(const CInstruction& rhs);

	bool ToBinary(ofstream& ofs);

	unsigned int Size();
	int TextFieldValueToInt(int iParamNum, string& sTextField);
	string IntFieldValueToText(int iParamNum);
	int TextOperatorToInt(string& sTextOperator);
	string IntOperatorToText(int iOperator);

	bool SetInstructionType(INSTRUCTION_OP_CODE_SPEC_T eOpCode);
	bool SetInstructionType(string& sInstructionText);

	INSTRUCTION_OP_CODE_SPEC_T m_InstructionOpCode;
	string m_InstructionText;
	unsigned int m_NumParamsUsed;
	string m_ParamNames[MAX_INST_PARAMS];
	unsigned int m_ParamValues[MAX_INST_PARAMS];
};

typedef list<CInstruction*> t_InstructionList;
typedef list<CInstruction*>::iterator t_InstructionListIter;

class CInstructions: public CErdBase {
public:
	CInstructions();
	virtual ~CInstructions(void);

	// copy constructor
	CInstructions(const CInstructions& rhs);
	// assignment operator
	virtual CInstructions& operator=(const CInstructions& rhs);

	virtual void Reset();

	static const string Begin;	// "Instructions"
	static const string End;	// "End Instructions"
	virtual const string& PackageName() {
		return Begin;
	}

	virtual bool Parse(CTimDescriptor& TimDescriptor,
			CTimDescriptorLine*& pLine, bool bIsBlf);

	virtual bool ToBinary(ofstream& ofs);
	virtual unsigned int PackageSize();
	virtual int AddPkgStrings(CReservedPackageData* pRPD);

	unsigned int NumInst();

	bool ParseLabels(CTimDescriptor& TimDescriptor,
			CTimDescriptorLine*& pInstructionsLine, bool bIsBlf);

	string* AttachLabel(string& sLabel);

	void DeleteLabels();

	enum eNumFields {
		INSTRUCTION_MAX = 0
	};
	t_InstructionList m_InstructionsList;

//    static t_stringList m_Labels;
	t_stringList m_Labels;

	static t_InstructionList s_InstFmt;
	static int s_InstCount;
};
#endif //__INSTRUCTIONS_H__
