
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2015 Francois Beaune, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

// appleseed-max headers.
#include "common/iappleseedmtl.h"

// appleseed.foundation headers.
#include "foundation/platform/windows.h"    // include before 3ds Max headers
#include "foundation/utility/autoreleaseptr.h"

// 3ds Max headers.
#include <color.h>
#include <IMaterialBrowserEntryInfo.h>
#include <imtl.h>
#include <iparamb2.h>
#include <maxtypes.h>
#include <ref.h>
#include <strbasic.h>
#undef base_type

// Forward declarations.
namespace renderer  { class Material; }
class BaseInterface;
class Bitmap;
class Color;
class FPInterface;
class ILoad;
class Interval;
class ISave;
class ShadeContext;

class AppleseedStdMtl
  : public Mtl
  , public IAppleseedMtl
{
  public:
    static Class_ID get_class_id();

    // Constructor.
    AppleseedStdMtl();

    // InterfaceServer methods.
    virtual BaseInterface* GetInterface(Interface_ID id) override;

    // Animatable methods.
    virtual void DeleteThis() override;
    virtual void GetClassName(TSTR& s) override;
    virtual SClass_ID SuperClassID() override;
    virtual Class_ID ClassID() override;
    virtual int NumSubs() override;
    virtual Animatable* SubAnim(int i) override;
    virtual TSTR SubAnimName(int i) override;
    virtual int SubNumToRefNum(int subNum) override;
    virtual int NumParamBlocks() override;
    virtual IParamBlock2* GetParamBlock(int i) override;
    virtual IParamBlock2* GetParamBlockByID(BlockID id) override;

    // ReferenceMaker methods.
    virtual int NumRefs() override;
    virtual RefTargetHandle GetReference(int i) override;
    virtual void SetReference(int i, RefTargetHandle rtarg) override;
    virtual RefResult NotifyRefChanged(
        const Interval&     changeInt,
        RefTargetHandle     hTarget,
        PartID&             partID,
        RefMessage          message,
        BOOL                propagate) override;

    // ReferenceTarget methods.
    virtual RefTargetHandle Clone(RemapDir &remap) override;

    // MtlBase methods.
    virtual void Update(TimeValue t, Interval& valid) override;
    virtual void Reset() override;
    virtual Interval Validity(TimeValue t) override;
    virtual ParamDlg* CreateParamDlg(HWND hwMtlEdit, IMtlParams* imp) override;
    virtual IOResult Save(ISave* isave) override;
    virtual IOResult Load(ILoad* iload) override;

    // Mtl methods.
    virtual Color GetAmbient(int mtlNum, BOOL backFace) override;
    virtual Color GetDiffuse(int mtlNum, BOOL backFace) override;
    virtual Color GetSpecular(int mtlNum, BOOL backFace) override;
    virtual float GetShininess(int mtlNum, BOOL backFace) override;
    virtual float GetShinStr(int mtlNum, BOOL backFace) override;
    virtual float GetXParency(int mtlNum, BOOL backFace) override;
    virtual void SetAmbient(Color c, TimeValue t) override;
    virtual void SetDiffuse(Color c, TimeValue t) override;
    virtual void SetSpecular(Color c, TimeValue t) override;
    virtual void SetShininess(float v, TimeValue t) override;
    virtual void Shade(ShadeContext& sc) override;

    // IAppleseedMtl methods.
    virtual foundation::auto_release_ptr<renderer::Material> create_material(const char* name) override;

  private:
    IParamBlock2*   m_pblock;
    Color           m_base_color;
};


//
// AppleseedStdMtl material browser info.
//

class AppleseedStdMtlBrowserEntryInfo
  : public IMaterialBrowserEntryInfo
{
  public:
    virtual const MCHAR* GetEntryName() const override;
    virtual const MCHAR* GetEntryCategory() const override;
    virtual Bitmap* GetEntryThumbnail() const override;
};


//
// AppleseedStdMtl class descriptor.
//

class AppleseedStdMtlClassDesc
  : public ClassDesc2
{
  public:
    virtual int IsPublic() override;
    virtual void* Create(BOOL loading) override;
    virtual const MCHAR* ClassName() override;
    virtual SClass_ID SuperClassID() override;
    virtual Class_ID ClassID() override;
    virtual const MCHAR* Category() override;
    virtual const MCHAR* InternalName() override;
    virtual FPInterface* GetInterface(Interface_ID id) override;
    virtual HINSTANCE HInstance();

  private:
    AppleseedStdMtlBrowserEntryInfo m_browser_entry_info;
};

extern AppleseedStdMtlClassDesc g_appleseed_stdmtl_classdesc;