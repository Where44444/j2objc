// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
//  IOSReflection.h
//  JreEmulation
//
//  Created by Tom Ball on 9/23/13.
//

#ifndef JreEmulation_IOSReflection_h
#define JreEmulation_IOSReflection_h

#include "IOSMetadata.h"
#include "J2ObjC_common.h"
#include "java/lang/reflect/Modifier.h"

#import "objc/runtime.h"

@class IOSClass;
@class JavaLangReflectConstructor;
@class JavaLangReflectField;
@class JavaLangReflectMethod;

// An empty class info struct to be used by certain kinds of class objects like
// arrays and proxies.
FOUNDATION_EXPORT const J2ObjcClassInfo JreEmptyClassInfo;

CF_EXTERN_C_BEGIN

IOSClass *JreClassForString(const char *str);
IOSObjectArray *JreParseClassList(const char *listStr);
Method JreFindInstanceMethod(Class cls, SEL selector);
Method JreFindClassMethod(Class cls, SEL selector);

__attribute__((always_inline)) inline const void *JrePtrAtIndex(const void **ptrTable, ptr_idx i) {
  return i < 0 ? NULL : ptrTable[i];
}


// Field and method lookup functions.
const J2ObjcFieldInfo *JreFindFieldInfo(const J2ObjcClassInfo *metadata, const char *fieldName) J2OBJC_METHOD_ATTR;
// Find a field declared in the given class
JavaLangReflectField *FindDeclaredField(
    IOSClass *iosClass, NSString *name, jboolean publicOnly) J2OBJC_METHOD_ATTR;
// Find a field declared in the given class or its hierarchy
JavaLangReflectField *FindField(
    IOSClass *iosClass, NSString *name, jboolean publicOnly) J2OBJC_METHOD_ATTR;
// Find a method or constructor declared in the given class.
JavaLangReflectMethod *JreMethodWithNameAndParamTypes(
    IOSClass *iosClass, NSString *name, IOSObjectArray *paramTypes) J2OBJC_METHOD_ATTR;
JavaLangReflectConstructor *JreConstructorWithParamTypes(
    IOSClass *iosClass, IOSObjectArray *paramTypes) J2OBJC_METHOD_ATTR;
JavaLangReflectMethod *JreMethodForSelector(IOSClass *iosClass, SEL selector) J2OBJC_METHOD_ATTR;
JavaLangReflectConstructor *JreConstructorForSelector(IOSClass *iosClass, SEL selector) J2OBJC_METHOD_ATTR;
// Find a method in the given class or its hierarchy.
JavaLangReflectMethod *JreMethodWithNameAndParamTypesInherited(
    IOSClass *iosClass, NSString *name, IOSObjectArray *types) J2OBJC_METHOD_ATTR;
JavaLangReflectMethod *JreMethodForSelectorInherited(IOSClass *iosClass, SEL selector) J2OBJC_METHOD_ATTR;
// Returns a string representation of the metadata.
NSString *JreMetadataToString(IOSClass *iosClass) J2OBJC_METHOD_ATTR;

// J2ObjcMethodInfo accessor functions.
NSString *JreMethodGenericString(const J2ObjcMethodInfo *metadata, const void **ptrTable) J2OBJC_METHOD_ATTR;

__attribute__((always_inline)) inline const char *JreMethodJavaName(
    const J2ObjcMethodInfo *metadata, const void **ptrTable)  J2OBJC_METHOD_ATTR {
  const char *javaName = (const char *)JrePtrAtIndex(ptrTable, metadata->javaNameIdx);
  return javaName ? javaName : sel_getName(metadata->selector);
}

// metadata must not be NULL.
__attribute__((always_inline)) inline SEL JreMethodSelector(const J2ObjcMethodInfo *metadata) J2OBJC_METHOD_ATTR {
  return metadata->selector;
}

CF_EXTERN_C_END

#endif // JreEmulation_IOSReflection_h
