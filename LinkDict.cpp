// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME LinkDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "gsang.h"
#include "tree.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *DGSEVENT_Dictionary();
   static void DGSEVENT_TClassManip(TClass*);
   static void *new_DGSEVENT(void *p = 0);
   static void *newArray_DGSEVENT(Long_t size, void *p);
   static void delete_DGSEVENT(void *p);
   static void deleteArray_DGSEVENT(void *p);
   static void destruct_DGSEVENT(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DGSEVENT*)
   {
      ::DGSEVENT *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::DGSEVENT));
      static ::ROOT::TGenericClassInfo 
         instance("DGSEVENT", "tree.h", 31,
                  typeid(::DGSEVENT), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &DGSEVENT_Dictionary, isa_proxy, 4,
                  sizeof(::DGSEVENT) );
      instance.SetNew(&new_DGSEVENT);
      instance.SetNewArray(&newArray_DGSEVENT);
      instance.SetDelete(&delete_DGSEVENT);
      instance.SetDeleteArray(&deleteArray_DGSEVENT);
      instance.SetDestructor(&destruct_DGSEVENT);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DGSEVENT*)
   {
      return GenerateInitInstanceLocal((::DGSEVENT*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::DGSEVENT*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *DGSEVENT_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::DGSEVENT*)0x0)->GetClass();
      DGSEVENT_TClassManip(theClass);
   return theClass;
   }

   static void DGSEVENT_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *wuDGSEVENT_Dictionary();
   static void wuDGSEVENT_TClassManip(TClass*);
   static void *new_wuDGSEVENT(void *p = 0);
   static void *newArray_wuDGSEVENT(Long_t size, void *p);
   static void delete_wuDGSEVENT(void *p);
   static void deleteArray_wuDGSEVENT(void *p);
   static void destruct_wuDGSEVENT(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::wuDGSEVENT*)
   {
      ::wuDGSEVENT *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::wuDGSEVENT));
      static ::ROOT::TGenericClassInfo 
         instance("wuDGSEVENT", "tree.h", 58,
                  typeid(::wuDGSEVENT), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &wuDGSEVENT_Dictionary, isa_proxy, 4,
                  sizeof(::wuDGSEVENT) );
      instance.SetNew(&new_wuDGSEVENT);
      instance.SetNewArray(&newArray_wuDGSEVENT);
      instance.SetDelete(&delete_wuDGSEVENT);
      instance.SetDeleteArray(&deleteArray_wuDGSEVENT);
      instance.SetDestructor(&destruct_wuDGSEVENT);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::wuDGSEVENT*)
   {
      return GenerateInitInstanceLocal((::wuDGSEVENT*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::wuDGSEVENT*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *wuDGSEVENT_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::wuDGSEVENT*)0x0)->GetClass();
      wuDGSEVENT_TClassManip(theClass);
   return theClass;
   }

   static void wuDGSEVENT_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *DFMAEVENT_Dictionary();
   static void DFMAEVENT_TClassManip(TClass*);
   static void *new_DFMAEVENT(void *p = 0);
   static void *newArray_DFMAEVENT(Long_t size, void *p);
   static void delete_DFMAEVENT(void *p);
   static void deleteArray_DFMAEVENT(void *p);
   static void destruct_DFMAEVENT(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DFMAEVENT*)
   {
      ::DFMAEVENT *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::DFMAEVENT));
      static ::ROOT::TGenericClassInfo 
         instance("DFMAEVENT", "tree.h", 106,
                  typeid(::DFMAEVENT), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &DFMAEVENT_Dictionary, isa_proxy, 4,
                  sizeof(::DFMAEVENT) );
      instance.SetNew(&new_DFMAEVENT);
      instance.SetNewArray(&newArray_DFMAEVENT);
      instance.SetDelete(&delete_DFMAEVENT);
      instance.SetDeleteArray(&deleteArray_DFMAEVENT);
      instance.SetDestructor(&destruct_DFMAEVENT);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DFMAEVENT*)
   {
      return GenerateInitInstanceLocal((::DFMAEVENT*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::DFMAEVENT*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *DFMAEVENT_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::DFMAEVENT*)0x0)->GetClass();
      DFMAEVENT_TClassManip(theClass);
   return theClass;
   }

   static void DFMAEVENT_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_DGSEVENT(void *p) {
      return  p ? new(p) ::DGSEVENT : new ::DGSEVENT;
   }
   static void *newArray_DGSEVENT(Long_t nElements, void *p) {
      return p ? new(p) ::DGSEVENT[nElements] : new ::DGSEVENT[nElements];
   }
   // Wrapper around operator delete
   static void delete_DGSEVENT(void *p) {
      delete ((::DGSEVENT*)p);
   }
   static void deleteArray_DGSEVENT(void *p) {
      delete [] ((::DGSEVENT*)p);
   }
   static void destruct_DGSEVENT(void *p) {
      typedef ::DGSEVENT current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::DGSEVENT

namespace ROOT {
   // Wrappers around operator new
   static void *new_wuDGSEVENT(void *p) {
      return  p ? new(p) ::wuDGSEVENT : new ::wuDGSEVENT;
   }
   static void *newArray_wuDGSEVENT(Long_t nElements, void *p) {
      return p ? new(p) ::wuDGSEVENT[nElements] : new ::wuDGSEVENT[nElements];
   }
   // Wrapper around operator delete
   static void delete_wuDGSEVENT(void *p) {
      delete ((::wuDGSEVENT*)p);
   }
   static void deleteArray_wuDGSEVENT(void *p) {
      delete [] ((::wuDGSEVENT*)p);
   }
   static void destruct_wuDGSEVENT(void *p) {
      typedef ::wuDGSEVENT current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::wuDGSEVENT

namespace ROOT {
   // Wrappers around operator new
   static void *new_DFMAEVENT(void *p) {
      return  p ? new(p) ::DFMAEVENT : new ::DFMAEVENT;
   }
   static void *newArray_DFMAEVENT(Long_t nElements, void *p) {
      return p ? new(p) ::DFMAEVENT[nElements] : new ::DFMAEVENT[nElements];
   }
   // Wrapper around operator delete
   static void delete_DFMAEVENT(void *p) {
      delete ((::DFMAEVENT*)p);
   }
   static void deleteArray_DFMAEVENT(void *p) {
      delete [] ((::DFMAEVENT*)p);
   }
   static void destruct_DFMAEVENT(void *p) {
      typedef ::DFMAEVENT current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::DFMAEVENT

namespace ROOT {
   static TClass *vectorlEwuDGSEVENTgR_Dictionary();
   static void vectorlEwuDGSEVENTgR_TClassManip(TClass*);
   static void *new_vectorlEwuDGSEVENTgR(void *p = 0);
   static void *newArray_vectorlEwuDGSEVENTgR(Long_t size, void *p);
   static void delete_vectorlEwuDGSEVENTgR(void *p);
   static void deleteArray_vectorlEwuDGSEVENTgR(void *p);
   static void destruct_vectorlEwuDGSEVENTgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<wuDGSEVENT>*)
   {
      vector<wuDGSEVENT> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<wuDGSEVENT>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<wuDGSEVENT>", -2, "vector", 214,
                  typeid(vector<wuDGSEVENT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEwuDGSEVENTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<wuDGSEVENT>) );
      instance.SetNew(&new_vectorlEwuDGSEVENTgR);
      instance.SetNewArray(&newArray_vectorlEwuDGSEVENTgR);
      instance.SetDelete(&delete_vectorlEwuDGSEVENTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEwuDGSEVENTgR);
      instance.SetDestructor(&destruct_vectorlEwuDGSEVENTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<wuDGSEVENT> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<wuDGSEVENT>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEwuDGSEVENTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<wuDGSEVENT>*)0x0)->GetClass();
      vectorlEwuDGSEVENTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEwuDGSEVENTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEwuDGSEVENTgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<wuDGSEVENT> : new vector<wuDGSEVENT>;
   }
   static void *newArray_vectorlEwuDGSEVENTgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<wuDGSEVENT>[nElements] : new vector<wuDGSEVENT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEwuDGSEVENTgR(void *p) {
      delete ((vector<wuDGSEVENT>*)p);
   }
   static void deleteArray_vectorlEwuDGSEVENTgR(void *p) {
      delete [] ((vector<wuDGSEVENT>*)p);
   }
   static void destruct_vectorlEwuDGSEVENTgR(void *p) {
      typedef vector<wuDGSEVENT> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<wuDGSEVENT>

namespace ROOT {
   static TClass *vectorlEDGSEVENTgR_Dictionary();
   static void vectorlEDGSEVENTgR_TClassManip(TClass*);
   static void *new_vectorlEDGSEVENTgR(void *p = 0);
   static void *newArray_vectorlEDGSEVENTgR(Long_t size, void *p);
   static void delete_vectorlEDGSEVENTgR(void *p);
   static void deleteArray_vectorlEDGSEVENTgR(void *p);
   static void destruct_vectorlEDGSEVENTgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<DGSEVENT>*)
   {
      vector<DGSEVENT> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<DGSEVENT>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<DGSEVENT>", -2, "vector", 214,
                  typeid(vector<DGSEVENT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEDGSEVENTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<DGSEVENT>) );
      instance.SetNew(&new_vectorlEDGSEVENTgR);
      instance.SetNewArray(&newArray_vectorlEDGSEVENTgR);
      instance.SetDelete(&delete_vectorlEDGSEVENTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEDGSEVENTgR);
      instance.SetDestructor(&destruct_vectorlEDGSEVENTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<DGSEVENT> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<DGSEVENT>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEDGSEVENTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<DGSEVENT>*)0x0)->GetClass();
      vectorlEDGSEVENTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEDGSEVENTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEDGSEVENTgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<DGSEVENT> : new vector<DGSEVENT>;
   }
   static void *newArray_vectorlEDGSEVENTgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<DGSEVENT>[nElements] : new vector<DGSEVENT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEDGSEVENTgR(void *p) {
      delete ((vector<DGSEVENT>*)p);
   }
   static void deleteArray_vectorlEDGSEVENTgR(void *p) {
      delete [] ((vector<DGSEVENT>*)p);
   }
   static void destruct_vectorlEDGSEVENTgR(void *p) {
      typedef vector<DGSEVENT> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<DGSEVENT>

namespace ROOT {
   static TClass *vectorlEDFMAEVENTgR_Dictionary();
   static void vectorlEDFMAEVENTgR_TClassManip(TClass*);
   static void *new_vectorlEDFMAEVENTgR(void *p = 0);
   static void *newArray_vectorlEDFMAEVENTgR(Long_t size, void *p);
   static void delete_vectorlEDFMAEVENTgR(void *p);
   static void deleteArray_vectorlEDFMAEVENTgR(void *p);
   static void destruct_vectorlEDFMAEVENTgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<DFMAEVENT>*)
   {
      vector<DFMAEVENT> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<DFMAEVENT>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<DFMAEVENT>", -2, "vector", 214,
                  typeid(vector<DFMAEVENT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEDFMAEVENTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<DFMAEVENT>) );
      instance.SetNew(&new_vectorlEDFMAEVENTgR);
      instance.SetNewArray(&newArray_vectorlEDFMAEVENTgR);
      instance.SetDelete(&delete_vectorlEDFMAEVENTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEDFMAEVENTgR);
      instance.SetDestructor(&destruct_vectorlEDFMAEVENTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<DFMAEVENT> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<DFMAEVENT>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEDFMAEVENTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<DFMAEVENT>*)0x0)->GetClass();
      vectorlEDFMAEVENTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEDFMAEVENTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEDFMAEVENTgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<DFMAEVENT> : new vector<DFMAEVENT>;
   }
   static void *newArray_vectorlEDFMAEVENTgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<DFMAEVENT>[nElements] : new vector<DFMAEVENT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEDFMAEVENTgR(void *p) {
      delete ((vector<DFMAEVENT>*)p);
   }
   static void deleteArray_vectorlEDFMAEVENTgR(void *p) {
      delete [] ((vector<DFMAEVENT>*)p);
   }
   static void destruct_vectorlEDFMAEVENTgR(void *p) {
      typedef vector<DFMAEVENT> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<DFMAEVENT>

namespace {
  void TriggerDictionaryInitialization_LinkDict_Impl() {
    static const char* headers[] = {
"gsang.h",
"tree.h",
0
    };
    static const char* includePaths[] = {
"/opt/ROOT/root61206/include",
"/data/d2/agafa_wuhongyi/gsort/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "LinkDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
struct __attribute__((annotate("$clingAutoload$tree.h")))  wuDGSEVENT;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
struct __attribute__((annotate("$clingAutoload$tree.h")))  DFMAEVENT;
struct __attribute__((annotate("$clingAutoload$tree.h")))  DGSEVENT;
typedef struct DGSEVENT DGSEVENT __attribute__((annotate("$clingAutoload$tree.h"))) ;
typedef struct wuDGSEVENT wuDGSEVENT __attribute__((annotate("$clingAutoload$tree.h"))) ;
typedef struct DFMAEVENT DFMAEVENT __attribute__((annotate("$clingAutoload$tree.h"))) ;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "LinkDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "gsang.h"
#include "tree.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"DFMAEVENT", payloadCode, "@",
"DGSEVENT", payloadCode, "@",
"wuDGSEVENT", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("LinkDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_LinkDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_LinkDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_LinkDict() {
  TriggerDictionaryInitialization_LinkDict_Impl();
}
