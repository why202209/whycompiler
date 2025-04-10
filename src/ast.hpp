#pragma once
#include <memory>
#include <string>
#include <vector>
#include<iostream>

// 所有 AST 的基类
class BaseAST {
    public:
     virtual ~BaseAST() = default;
     virtual void Dump() const = 0;
};
   
// CompUnit 是 BaseAST
class CompUnitAST : public BaseAST {
    public:
     // 用智能指针管理对象
     std::unique_ptr<BaseAST> func_def;

     void Dump() const override {
       /*std::cout << "CompUnitAST { ";*/
       func_def->Dump();
       /*std::cout << " }";*/
     }
};
   
// FuncDef 也是 BaseAST
class FuncDefAST : public BaseAST {
    public:
     std::unique_ptr<BaseAST> func_type;
     std::string ident;
     std::unique_ptr<BaseAST> block;

     void Dump() const override {
       /*std::cout << "FuncDefAST { ";
       func_type->Dump();
       std::cout << ", " << ident << ", ";
       block->Dump();
       std::cout << " }";*/
       std::cout<<"fun @"<<ident<<"(): ";
       func_type->Dump();
       std::cout<<" ";
       block->Dump();
       //std::cout<<std::endl;
     }
};
   
// ...
class FuncTypeAST : public BaseAST{
    public:
    std::string type;
    
    void Dump() const override {
        /*std::cout << "FuncTypeAST { ";
        std::cout << type;
        std::cout << " }";*/
        std::cout<<"i32";
    }
};

//
class StmtAST:public BaseAST{
    public:
    std::unique_ptr<std::string> sentence;
    int retval;
    std::unique_ptr<BaseAST> num;

    void Dump() const override {
        /*std::cout << "StmtAST { ";
        std::cout << retval;
        std::cout << " }";*/
        std::cout<<"  ret ";//<<std::endl;
        num->Dump();
    }
};

//
class BlockAST :public BaseAST{
    public:
    std::unique_ptr<BaseAST> stmt;

    void Dump() const override {
        /*std::cout << "BlockAST { ";
        stmt->Dump();
        std::cout << " }";*/
        std::cout << "{ "<<std::endl;
        std::cout<<"%entry:"<<std::endl;
        stmt->Dump();
        std::cout << "}"<<std::endl;
    }
};

//
class NumberAST: public BaseAST{
    public:
    int val;

    void Dump() const override {
        std::cout<<val;
        std::cout<<std::endl;
    }
};