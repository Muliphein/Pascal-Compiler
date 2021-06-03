# Report

#### Abstract

In the Compile Principle course, we learn about the Basic method to generate a Compiler.

The final Project is to make a simple compiler of the SPL, which is reduced from the Pascal.

In this project, we use the Flex, Bison and LLVM to get tokens, build the syntax tree and build the IR codes and assembly code respectively.

Our development language is C++. The build environment is Windows Subsystem Linux.

### Introduction

### Lexical Analysis

### Syntax Analysis

### Semantic Analysis & Code Generation

In this section, I'm going to introduce the Sematic Analysis, which includes the symbol table and the type check. At the same time, we also generate the IR code. In this part, we need to maintain some symbol tables so that make sure that there is no wrong in the code.

#### Symbol Table

When it comes to symbol tables, we take the record, variable into consideration.

##### Record Type Table

For the record, we need to note down the name of the record, and we can use the name of the record as a new variable type conveniently. We use the data structure below to maintain the information of all the record.

```c++
std::map<Type*, std::vector<Type*> > record_type_list;// StructType -> Member_Type_List
std::map<Type*, std::vector<std::string> > record_member_name_list;// StructType -> Member_Name_List
std::map<Type*, std::vector<bool> > record_member_array;// StructType -> Member_Name_List

```

We use the pointer to Type as the index to get the information of the record. use this pointer, we can get the member list of the record easily, and know whether the member is array or not. What's more, we can get the type list. As a result, when we meet a record type, we can recursively access it's member.

Surely, there is a condition that record type which is nested exists. To deal with this, we build others to maintain the information.

```c++
std::map<std::string, Type*> type_map;// TypeName -> Type Pointer
std::map<Type*, std::string> name_map;// Type -> TypeName Pointer
```

we can use the type name, which is shown as a string, to search the type pointer. After that, we can access the details of the record through the type pointer. To make the logic same as the native type, at the beginning of the program, I insert the native information to the table.

```c++
type_map["char"] = ByteType;
name_map[ByteType] = "char";
zero_initial[ByteType] = ConstantInt::get(ByteType, 0);
type_map["integer"] = IntType;
name_map[IntType] = "integer";
zero_initial[IntType] = ConstantInt::get(IntType, 0);
type_map["real"] = RealType;
name_map[RealType] = "real";
zero_initial[RealType] = ConstantFP::get(RealType, 0);
type_map["bool"] = BoolType;
name_map[BoolType] = "bool";
zero_initial[BoolType] = ConstantInt::get(BoolType, 0);
type_map["void"] = VoidType;
name_map[VoidType] = "void";
```

So that, we can use the record as the native type, which means it can deal with the nest type conveniently. The same logic make the access much more easily.

##### Variable Table

After discussing the record type, we are going to discuss about the design of the variable table. As we discuss above, we treat the record type as one of the type which is similar to native type. there is no need to consider the record anymore. What we only need to pay attention to is the local variable and global variable.

We use the new data structure to maintain the information of the different level's variable.

```c++
int stage;
std::map<std::string, Value*> table_mem[MAX_NESTED];// VarName -> Memory
std::map<std::string, Type*> table_type[MAX_NESTED];// VarName -> Type
std::map<std::string, bool> table_array[MAX_NESTED];// VarName -> Array
```

In these vectors, I store the links of the variable's name and the memory pointer, and the type, whether is array or not. Each time, when we need the information, we can use the map directly and get the information. I use the index of the vector array to show the region of the variable. If the index is 0, it involve the global variable. When the index is bigger than 0, it means the local variable.

When we enter a region which may have the local variables, we need to increase the value of the stage, so that, we can create a new table for the local variables. And we don't check the re-definition of the variable which is at different level, but access the low level variables. 

##### Type Check & Cast

##### 