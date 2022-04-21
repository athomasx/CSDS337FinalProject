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
  		if(step){
  			expression.push_back(step->Val);
  		}
  		else{
  
  		}
  
  		NumberExprAST* start = dynamic_cast<NumberExprAST*>(loop->Start.get());
  		if(start){
  			expression.push_back(start->Val);
  			printf(" this is 1: %f \n", start->Val);
  		}else{
  	
  		}
  		BinaryExprAST* end = dynamic_cast<BinaryExprAST*>(loop->End.get());
  		if(end){
  
  			NumberExprAST* rvalue = dynamic_cast<NumberExprAST*>(end->RHS.get());
  			if(rvalue){
  				printf(" this is supposed to be n: %f \n", rvalue->Val);
  				expression.push_back(rvalue->Val);
  			}
  		}
  	}
  	return expression;
  }
  
  void ExamplePass(ModuleAST* TheModule) {
  //fprintf(stderr, "This Module has %lu externs and %lu functions!\n\n",
  	for(auto const& n : TheModule->Functions){
  		FunctionAST* func = n.second.first.get();
  		ForExprAST* loop;
  		BinaryExprAST* body = dynamic_cast<BinaryExprAST*>(func->Body.get());
  
  		ForExprAST* RValue = dynamic_cast<ForExprAST*>(body->RHS.get());
  		ForExprAST* LValue = dynamic_cast<ForExprAST*>(body->LHS.get());
  
  		std::vector<double> exp1 = FindLoopExpression(RValue);
  		std::vector<double> exp2 = FindLoopExpression(LValue);

  		if(exp1.size() == 3 && exp2.size() == 3){
    			bool check = true;
    			for(int i = 0; i < 3; i++){
    	  			if(exp1.at(i) != exp2.at(i)){
					check = false;
					//printf("Incorrect headers: %f %f \n", exp1.at(i), exp2.at(i));
      	  			}
    			}
    			if(check){
      				printf("test");
    			}		
  		}	
 	}
 }

