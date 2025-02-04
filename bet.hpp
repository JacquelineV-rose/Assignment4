bool isOperand(string expression);

int checkPrecedence(string expression);











BET::BET(){


    start = nullptr;

}




BET::BET(const string postfix){

    start = nullptr;

    buildFromPostfix(postfix);


}




BET::BET(const BET& rhs){


    start = clone(rhs.start);

}




BET::~BET(){

makeEmpty(start);


}



bool BET::empty(){

    return start == nullptr;

}




const BET& BET::operator=(const BET& rhs){


if (this != &rhs){

    makeEmpty(start);
    start = clone(rhs.start);


}

    return *this;

}






bool BET::buildFromPostfix(const string& postfix){ 

	string n1;
	string n2;

		
	int counter1 = 0;
	int counter2 = 0;



	stack<BinaryNode*> myStack;


	stringstream s(postfix);
	

if(postfix.empty() == true){

		cout << "Not a postfix expression" << endl;

		start = nullptr;
		return false;
}
	


if(empty() == false)


	makeEmpty(start);
	


bool flag = false;
	

while(s >> n1){ 
		
	BinaryNode *myNode = new BinaryNode(n1); 
		

	if(isOperand(n1) == true){ 
		counter1++;
		myStack.push(myNode);


}else if(checkPrecedence(n1) != 0){	



	counter2++;


if(counter1 == counter2){

	cout << "Wrong postfix expression" << endl;

	start = nullptr;
	return false;


}else{


	myNode->left = myStack.top();

	myStack.pop();

	myNode->right = myStack.top();

	myStack.pop();

	myStack.push(myNode);

}
}		
}

if(counter1 != counter2)

	start = myStack.top();


if(myStack.empty() == true){ 

	cout << "Invalid" << endl;
	start = nullptr;
	return false;

}


return true;
}



void BET::printInfixExpression(){ 

	printInfixExpression(start);
	cout << endl;
}


bool isOperand(const string str){ 

for(int i = 0; i < int(str.size()); i++)
	if(isalnum(str[i]) == false)  

	return false;


	return true;
}



int checkPrecedence(const string str){ 
	if(str == "("|| str == ")")
		return (3);
	else if(str == "*" || str == "/")
		return (2);
	else if(str == "+" || str == "-")
		return (1);
	else
		return 0;
}





void BET::printInfixExpression(BinaryNode *n){ 

bool closeParentheses = false;
	

if(n != nullptr){

	if(n->left == nullptr && n->right == nullptr) 

        cout << n->element << " ";

else{

    if(checkPrecedence(n->element) != 0 && checkPrecedence(n->right->element) != 0){	

        if(checkPrecedence(n->element) >= checkPrecedence(n->right->element)){
				
				if(checkPrecedence(n->element) == 2){

					cout << "( ";
					closeParentheses = true;

	}
}
}
            
    printInfixExpression(n->right);
			
    
	if(closeParentheses == true)
		cout << ") ";

        closeParentheses = false; 

            
        cout << n->element << " ";


if(checkPrecedence(n->element) != 0 && checkPrecedence(n->left->element) != 0){	

	if(checkPrecedence(n->element) >= checkPrecedence(n->left->element)){

		cout << "( ";


		closeParentheses = true;

}
}
            
    printInfixExpression(n->left);


if(closeParentheses == true)

	cout << ") ";
	closeParentheses = false; 




    }
}
}






void BET::printPostfixExpression(){ 
	printPostfixExpression(start);
	cout << endl;
}





void BET::printPostfixExpression(BinaryNode* n){

if (n != nullptr){

    printPostfixExpression(n->left);
    printPostfixExpression(n->right);


    
	cout << n->element << " ";


}
}




void BET::makeEmpty(BinaryNode*& t){


if (t != nullptr){

    makeEmpty(t->left);
    makeEmpty(t->right);

    delete t;

    t = nullptr;

}
}




BET::BinaryNode* BET::clone(BinaryNode* t) const{


    if (t == nullptr) return nullptr;

    return new BinaryNode(t->element, clone(t->left), clone(t->right));

}




size_t BET::size(){

    return size(start);
}




size_t BET::size(BinaryNode* t){

    if (t == nullptr) return 0;


    return 1 + size(t->left) + size(t->right);
}



size_t BET::leaf_nodes(){


    return leaf_nodes(start);

}






size_t BET::leaf_nodes(BinaryNode* t){


if (t == nullptr) return 0;

    if (t->left == nullptr && t->right == nullptr) return 1;

    return leaf_nodes(t->left) + leaf_nodes(t->right);

}
