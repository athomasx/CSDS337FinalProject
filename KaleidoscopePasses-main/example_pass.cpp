#include "AST.h"
#include <iostream>
#include <map>
#include <vector>
#include "llvm/IR/Value.h"


  
  std::vector<double> findloopheader(ForExprAST* forloop){
  	std::vector<double> header;
  
  	if(forloop){
  		ExprAST* body1 = forloop->Body.get();
  		NumberExprAST* step = dynamic_cast<NumberExprAST*>(forloop->Step.get());
  		if(step){
  			header.push_back(step->Val);
  		}
  		else{
  
  		}
  
  		NumberExprAST* start = dynamic_cast<NumberExprAST*>(forloop->Start.get());
  		if(start){
  			header.push_back(start->Val);
  			printf(" this is 1: %f \n", start->Val);
  		}else{
  	
  		}
  		BinaryExprAST* end = dynamic_cast<BinaryExprAST*>(forloop->End.get());
  		if(end){
  
  			NumberExprAST* valueright = dynamic_cast<NumberExprAST*>(end->RHS.get());
  			if(valueright){
  				printf(" this is supposed to be n: %f \n", valueright->Val);
  				header.push_back(valueright->Val);
  			}
  		}
  	}
  	return header;
  }
  
  void ExamplePass(ModuleAST* TheModule) {
  //fprintf(stderr, "This Module has %lu externs and %lu functions!\n\n",
  	for(auto const& n : TheModule->Functions){
  		FunctionAST* func = n.second.first.get();
  		ForExprAST* forloop;
  		BinaryExprAST* exp = dynamic_cast<BinaryExprAST*>(func->Body.get());
  
  		ForExprAST* valueright = dynamic_cast<ForExprAST*>(exp->RHS.get());
  		ForExprAST* valueleft = dynamic_cast<ForExprAST*>(exp->LHS.get());
  
  		std::vector<double> header1 = findloopheader(valueright);
  		std::vector<double> header2 = findloopheader(valueleft);

  		if(header1.size() == 3 && header2.size() == 3){
    			bool same = true;
    			for(int i = 0; i < 3; i++){
    	  			if(header1.at(i) != header2.at(i)){
					same = false;
					printf("Incorrect headers: %f %f \n", header1.at(i), header2.at(i));
     	    				break;
      	  			}
    			}
    			if(same){
      				printf("test");
    			}		
  		}	
 	}
 }

