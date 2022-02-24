bool validoperand(string input);
bool validoperator(string input);
int precedence(string input);

//
// class BET member function definitions
//

// *****************************************************************
// * Function Name:  BET()                                         *
// * Description:  Default constructor that creates an empty       *
// * binary tree                                                   *
// * Parameter Description:  No parameters                         *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  No References                                    *
// *****************************************************************
BET::BET() {
    // Creates an empty tree
    root = new BinaryNode;
}

// *****************************************************************
// * Function Name:  BET()                                         *
// * Description:  Parametrized constructor that creates           *
// * a binary tree based on a postfix expression                   *
// * Parameter Description: strong postfix, used to create the tree*
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  No References                                    *
// *****************************************************************
BET::BET(const string &postfix) {
    // Creates an empty tree and
    // builds the tree based on
    // the postfix expression parameter
    root = new BinaryNode;
    buildFromPostfix(postfix);
}

// *****************************************************************
// * Function Name:  BET()                                         *
// * Description:  Copy constructor that creates copies all        *
// * nodes in a binary tree                                        *
// * Parameter Description: x, object used to copy its nodes       *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  Textbook                                         *
// *****************************************************************
BET::BET(const BET &x) {
    // Reference private helper function
    // to clone all nodes starting from the root
    root = clone(x.root);
}

// *****************************************************************
// * Function Name:  ~BET()                                        *
// * Description:  Destructor that deletes all the nodes in the    *
// * tree                                                          *
// * Parameter Description: No parameters                          *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  Textbook                                         *
// *****************************************************************
BET::~BET() {
    // Reference private helper function
    // to delete all nodes of the tree
    makeEmpty(root);
}

// *****************************************************************
// * Function Name:  buildFromPostfix()                            *
// * Description: Builds a binary tree based on its postfix        *
// * expression parameter                                          *
// * Parameter Description: string postfix, postfix expression     *
// * to build a binary tree                                        *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References: David Gaitros' Video on Postfix to Infix (Canvas) *
// *****************************************************************
bool BET::buildFromPostfix(const string &postfix) {
    // Declare variables/vectorStack and tokenize postfix parameter
    string token = postfix;
    vector<BinaryNode*> vectorStack;
    stringstream sstream(token);

    // If the postfix parameter is empty, yield an ERROR, return false
    // and set root == nullptr (empty tree)
    if(postfix.empty()){
        cout << "ERROR: Empty postfix expression" << endl;
        root = nullptr;
        return false;
    }

    // Read in postfix expression piece-by-piece
    while(sstream >> token){
        // Create a new node for each piece
        auto *myNode = new BinaryNode(token);

        // If token is an operand, push it to the stack
        // Else if token is an operator and there are fewer than
        // 2 values on the stack, yield an ERROR
        // Else, pop top 2 values from stack, and put
        // the operator as the node with it's children nodes
        // being the first/second popped values, push the root back to the stack
        if(validoperand(token)){
            vectorStack.push_back(myNode);	// push_back new node to stack
        }else if(validoperator(token) && (vectorStack.size() < 2)) {
            cout << "ERROR: Input not sufficient values in the expression" << endl;
            root = nullptr;
            return false;
        }else{
            myNode->left = vectorStack.back();
            vectorStack.pop_back();
            myNode->right = vectorStack.back();
            vectorStack.pop_back();
            vectorStack.push_back(myNode);
        }
    }

    // If stack size == 1, it must an operator,
    // set root of tree to that value
    // Else, there must be an error with the postfix
    // expression, yield error
    if((vectorStack.size() == 1)){
        root = vectorStack.back();
    }else{
        cout << "ERROR: Invalid expression" << endl;
        return false;
    }

    return true;
}

// *****************************************************************
// * Function Name:  operator=()                                   *
// * Description:  = operator overload that copies                 *
// * the nodes in a binary tree                                    *
// * Parameter Description: x, object used to copy over nodes      *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  No References                                    *
// *****************************************************************
const BET &BET::operator=(const BET &x) {
    // Use clone() private helper function to copy
    root = clone(x.root);
    return *this;
}

// *****************************************************************
// * Function Name:  printInfixExpression()                        *
// * Description:  Prints the infix expression given by the root   *
// * of the tree                                                   *
// * Parameter Description: No parameters                          *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  No References                                    *
// *****************************************************************
void BET::printInfixExpression() {
    // References private helper function
    // to print the infix expression starting
    // from the root of the tree
    printInfixExpression(root);
}

// *****************************************************************
// * Function Name:  printPostfixExpression()                      *
// * Description:  Prints the postfix expression given by the root *
// * of the tree                                                   *
// * Parameter Description: No parameters                          *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  No References                                    *
// *****************************************************************
void BET::printPostfixExpression() {
    // References private helper function
    // to print the postfix expression starting
    // from the root of the tree
    printPostfixExpression(root);
}

// *****************************************************************
// * Function Name:  size()                                        *
// * Description:  Returns size of the tree                        *
// * Parameter Description: No parameters                          *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  No References                                    *
// *****************************************************************
size_t BET::size() {
    // References private helper function
    // to return the size starting
    // from the root of the tree
    return size(root);
}

// *****************************************************************
// * Function Name:  leaf_nodes()                                  *
// * Description:  Returns the # of leaf nodes in the tree         *
// * Parameter Description: No parameters                          *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  No References                                    *
// *****************************************************************
size_t BET::leaf_nodes() {
    // References private helper function
    // to return the number of leaf nodes
    // starting from the root of the tree
    return leaf_nodes(root);
}

// *****************************************************************
// * Function Name:  empty()                                       *
// * Description:  Checks if the binary tree is empty              *
// * Parameter Description: No parameters                          *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  No References                                    *
// *****************************************************************
bool BET::empty() {
    // If root is nullptr, then the list is empty
    // thus return true, else return false
    if(root == nullptr){
        return true;
    }else{
        return false;
    }
}

//
// Private helper function definitions
//


// *****************************************************************
// * Function Name:  printInfixExpression()                        *
// * Description:  Prints infix expression from tree based off     *
// * parameter root                                                *
// * Parameter Description: n, used to base the infix expression   *
// * print                                                         *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References: David Gaitros' Video on Postfix to Infix (Canvas) *
// *****************************************************************
void BET::printInfixExpression(BET::BinaryNode *n) {
    bool flag = false;
    
    // If node is not empty...
    if(n != nullptr) {
        // If a leaf node... output just the node
        // Else, continue on with the algorithm
        if (n->left == nullptr && n->right == nullptr) {
            cout << n->element << " ";
        } else {
            // If the node and the right child are operators...
            if (validoperator(n->element) && validoperator(n->right->element)) {
                // Test if the precedence of the node is greater than the right child's
                if (precedence(n->element) >= precedence(n->right->element)) {
                    // If the node is a * or /, display a
                    // left parenthesis and set flag
                    if (precedence(n->element) == 1) {
                        cout << "( ";
                        flag = true;
                    }
                }
            }
            // Use recursion for the right child
            printInfixExpression(n->right);

            // If the flag is set, display the right parenthesis
            if (flag)
                cout << ") ";

            flag = false; // Reset flag

            // Display node
            cout << n->element << " ";
            // If the node and left child are operators...
            if (validoperator(n->element) && validoperator(n->left->element)) {
                // Test if the precedence of the node is greater than the left child's
                if (precedence(n->element) >= precedence(n->left->element)) {
                    // If the node is a * or /, display a
                    // left parenthesis and set flag
                    if(precedence(n->element) == 1) {
                        cout << "( ";
                        flag = true;
                    }
                }
            }
            // Use recursion for the left child
            printInfixExpression(n->left);

            // If the flag is set, display the right parenthesis
            if (flag)
                cout << ") ";
            flag = false; // Reset flag
        }
    }
}

// *****************************************************************
// * Function Name:  makeEmpty()                                   *
// * Description:  Deletes all of the nodes based off              *
// * parameter root                                                *
// * Parameter Description: t, base node to delete all nodes       *
// * past it                                                       *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  Textbook                                         *
// *****************************************************************
void BET::makeEmpty(BET::BinaryNode *&t) {
    // If t is not empty, make the
    // use recursion to delete the left
    // and right nodes, and delete the root
    // until all nodes are empty
    if( t != nullptr ){
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = nullptr;
}

// *****************************************************************
// * Function Name:  clone()                                       *
// * Description:  Copies all of the nodes based off parameter     *
// * root                                                          *
// * Parameter Description: t, base node to clone  all nodes       *
// * past it                                                       *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  Textbook                                         *
// *****************************************************************
BET::BinaryNode *BET::clone(BET::BinaryNode *t) {
    // If t == nullptr, return nullptr (nothing to clone)
    // Else, use recursion to clone each of the nodes
    // given by the left and right children and it's root
    if(t == nullptr){
        return nullptr;
    }else{
        return new BinaryNode(t->element, clone(t->left), clone(t->right));
    }
}

// *****************************************************************
// * Function Name:  printPostfixExpression()                      *
// * Description:  Prints postfix expression from tree based off   *
// * parameter root                                                *
// * Parameter Description: n, used to base the postfix expression *
// * print                                                         *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References: David Gaitros' Video on Postfix to Infix (Canvas) *
// *****************************************************************
void BET::printPostfixExpression(BET::BinaryNode *n) {
    // If size(n) == 0, Edge case to prevent segmentation fault (empty tree)
    // Else if children node are nullptrs, simply return the root node only
    // Else, use recursion to print children nodes following alongside the parameter's element
    if(size(n) == 0) {
        return;
    }else if(root->left == nullptr && root->right == nullptr) {
        cout << root->element << endl;
    }else{
        printPostfixExpression(n->right);
        printPostfixExpression(n->left);
        cout << n->element << " ";
    }
}

// *****************************************************************
// * Function Name:  size()                                        *
// * Description:  Returns size of the tree based off parameter    *
// * root                                                          *
// * Parameter Description: t, base node used to count the size    *
// * of the tree past it                                           *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  No References                                    *
// *****************************************************************
size_t BET::size(BET::BinaryNode *t) {
    // If t is nullptr, then it's empty, return 0
    // If not, use recursion to find the size pointed
    // by the left and right children + 1 (root)
    if(t == nullptr){
        return 0;
    }else{
        return (1+size(t->left)+size(t->right));
    }
}

// *****************************************************************
// * Function Name:  leaf_nodes()                                  *
// * Description:  Returns the # of leaf nodes in the tree based   *
// * off parameter root                                            *
// * Parameter Description: t, base node used to count the # of    *
// * leaf nodes in the tree past it                                *
// * Date:  02/10/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References:  No References                                    *
// *****************************************************************
size_t BET::leaf_nodes(BET::BinaryNode *t) {
    // If t == nullptr, then it's empty, return 0
    // Else if, left/right children of t == nullptr, return 1
    // Else, use recursion to find the number of leaf nodes
    // given by the left and right children
    if(t == nullptr){
        return 0;
    }else if((t->left == nullptr) && (t->right == nullptr)){
        return 1;
    }else{
        return (leaf_nodes(t->left)+leaf_nodes(t->right));
    }
}

//
// Custom functions for building tree from postfix expression by me
//

// *****************************************************************
// * Function Name:  validoperand()                                *
// * Description:  Determines if string is a valid operand         *
// * Parameter Description: string input used to check             *
// * Date:  02/11/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References: Code from Assignment 4                            *
// *****************************************************************
bool validoperand(string input){
    // If character is alphanumeric, return true, else return false
    for(char i: input){
        if(isalnum(i)){
            return true;
        }
    }
    return false;
}

// *****************************************************************
// * Function Name:  validoperator()                               *
// * Description:  Determines if string is a valid operator        *
// * Parameter Description: string input used to check             *
// * Date:  02/11/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References: Code from Assignment 4                            *
// *****************************************************************
bool validoperator(string input){
    // If input is an operator, then it is valid, return true, else false
    if(input == "*" || input == "/" || input == "+" || input == "-"){
        return true;
    }
    return false;
}

// *****************************************************************
// * Function Name:  precedence()                                  *
// * Description:  Checks precedence of operators + parenthesis    *
// * Parameter Description: string input used to check             *
// * Date:  02/11/2022                                             *
// * Author:   Peyton J. Smith                                     *
// * References: Code from Assignment 4                            *
// *****************************************************************
int precedence(string input){
    // Associate parenthesis/operator with a integer value according to precedence
    if (input == "(" || input == ")") {
        return 2;
    }else if(input == "*" || input == "/") {
        return 1;
    }else if(input == "+" || input == "-") {
        return 0;
    }else{ // Should never happen
        return -1;
    }
}