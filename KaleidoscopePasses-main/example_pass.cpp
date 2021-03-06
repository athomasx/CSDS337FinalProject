#include "AST.h"
#include <iostream>
#include <map>
#include <vector>
#include "llvm/IR/Value.h"


  
  std::vector<double> FindLoopExpression(ForExprAST* loop){
  	std::vector<double> expression;
  
  	if(loop){
  		ExprAST* body = loop->Body.get();
  		NumberExprAST* step = dynamic_cast<NumberExprAST*>(loop->Step.get());
  		NumberExprAST* start = dynamic_cast<NumberExprAST*>(loop->Start.get());
  		BinaryExprAST* end = dynamic_cast<BinaryExprAST*>(loop->End.get());
  		if(step && start && end){
  			expression.push_back(step->Val);
  			expression.push_back(start->Val);
  			NumberExprAST* RValue = dynamic_cast<NumberExprAST*>(end->RHS.get());
  			if(RValue){
  				expression.push_back(RValue->Val);
  			}
  		}
  		else{
  
  		}
  	}
  	return expression;
  }
  
  void ExamplePass(ModuleAST* TheModule) {
  	for(auto const& n : TheModule->Functions){
  		FunctionAST* func = n.second.first.get();
  		BinaryExprAST* body = dynamic_cast<BinaryExprAST*>(func->Body.get());
  
  		ForExprAST* RValue = dynamic_cast<ForExprAST*>(body->RHS.get());
  		std::vector<double> exp1 = FindLoopExpression(RValue);
  		
  		
  		ForExprAST* LValue = dynamic_cast<ForExprAST*>(body->LHS.get());		
  		std::vector<double> exp2 = FindLoopExpression(LValue);

  		if(exp1.size() == exp2.size()){
    	  		if((exp1.at(0) == exp2.at(0)) && (exp1.at(1) == exp2.at(1)) && (exp1.at(2) == exp2.at(2))){
    				BinaryExprAST* newLoop = new BinaryExprAST(':', nullptr, nullptr);
    				
    				newLoop->RHS.swap(RValue->Body);
    				newLoop->LHS.swap(LValue->Body);
    				
    				LValue->Body.reset(newLoop);
    				
    				func->Body.swap(body->LHS);
    			}		
  		}	
 	}
 }

