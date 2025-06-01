#pragma once
#include <memory>
#include <string>
#include <vector>
#include<iostream>

static int iridx = 0;

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
    int fg;
    /*std::unique_ptr<std::string> sentence;
    int retval;
    std::unique_ptr<BaseAST> num;*/
    std::unique_ptr<BaseAST> exp;

    void Dump() const override {
        //if (fg == 1) {
            /*std::cout << "StmtAST { ";
            std::cout << retval;
            std::cout << " }";*/
            //std::cout<<"  ret ";//<<std::endl;
            //num->Dump();
        //}
        if (fg == 2) {
            exp->Dump();
            std::cout<<"  ret %"<< iridx-1 <<std::endl;
        }
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

class ExpAST: public BaseAST{
    public:
    std::unique_ptr<BaseAST> unaryexp;

    void Dump() const override {
        unaryexp->Dump();
    }
};

class PrimaryExpAST: public BaseAST{
    public:
    int fg;
    std::unique_ptr<BaseAST> exp;

    void Dump() const override {
        if(fg==1) {
            exp->Dump();
        }
        else if(fg==2) {
            std::cout << "  %" << iridx << " = add 0, ";
            exp->Dump();
            iridx++;
        }
    }
};

class UnaryExpAST: public BaseAST{
    public:
    int fg;
    std::unique_ptr<BaseAST> primaryexp;
    char unaryop;
    std::unique_ptr<BaseAST> unaryexp;

    void Dump() const override {
        if (fg == 1) {
            primaryexp->Dump();
        }
        else if (fg == 2) {
            unaryexp->Dump();
            if(unaryop=='-') {
                std::cout << "  %" << iridx << " = sub 0, %";
                std::cout << iridx-1 <<std::endl;
                iridx++;
            }
            else if(unaryop=='!') {
                std::cout << "  %" << iridx << " = eq 0, %";
                std::cout << iridx-1 <<std::endl;
                iridx++;
            }
        }
    }
};
