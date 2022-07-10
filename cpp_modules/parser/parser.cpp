#include<iostream>
#include<vector>
#include<array>
#include<string>
#include<stdexcept>
#include<map>

using namespace std;

#define MAX_CHILD_PROCESS_SIZE 10

map <char, float> value_map;
map <char, size_t> precedence_map;
float null_float = NULL;

enum class Operator_ {plus, star, slash, hyphen, none};

struct Term
{
    protected:
        float value;
    public:
        virtual float get_value(){
            return this->value;
        }

        Term (){
            this->value = null_float;
        }

        Term (char c){
            this->value = value_map[c];
        }
};

struct BinaryOperator : public Term
{
    private:
        bool is_complete(){
            return this->child_terms[1] != nullptr && this->child_terms[0] != nullptr;
        }

    public:
        array<Term*, 2> child_terms;
        Operator_ operator_ ;

        BinaryOperator(){
            this->operator_ = Operator_::none;
        }

        BinaryOperator(Operator_ operator_){
            this->operator_ = operator_;
        }

        BinaryOperator(char operator_){
            switch (operator_)
            {
            case '+':
                this->operator_ = Operator_::plus;
                break;
            case '/':
                this->operator_ = Operator_::slash;
                break;
            case '-':
                this->operator_ = Operator_::hyphen;
                break;
            case '*':
                this->operator_ = Operator_::star;
                break;
            
            default:
                break;
            }
        }

        float get_value() override{

            if (this->value != NULL){
                return value;
            }

            if (this->is_complete()){
                switch (operator_){
                    case Operator_::plus:
                        this->value = (*(this->child_terms[0])).get_value() + (*(this->child_terms[1])).get_value(); 
                        break;
                    case Operator_::hyphen:
                        this->value = (*(this->child_terms[0])).get_value() - (*(this->child_terms[1])).get_value(); 
                        break;
                    case Operator_::star:
                        this->value = (*(this->child_terms[0])).get_value() * (*(this->child_terms[1])).get_value(); 
                        break;
                    case Operator_::slash:
                        this->value = (*(this->child_terms[0])).get_value() / (*(this->child_terms[1])).get_value(); 
                        break;
                    default:
                        break;
                } 
            }else{
                throw invalid_argument (" term should be complete");
            }
        }
    
        void add_child(Term * t){
            if (this->child_terms[0] == nullptr){
                child_terms[0] = t;
            }
            else{
                child_terms[1] = t;
            }
        }
    
};


bool char_is_a_variable(const char &c){
    return isalpha(c);
}

bool char_is_an_operator(const char &c){
    return (c == '+' ||  c == '*') || (c == '-' ||  c == '/');
}

bool char_is_a_left_parenthesis(const char &c){
    return c == '(';
}

bool char_is_a_right_parenthesis(const char &c){
    return c == ')';
}

char get_nearest_right_character(const string &s, int i){
    i+=1;
    while (s[i] == ' ' &&  i < s.length()) i++;
    if (i == -1 || i == s.length()) {return ' ';}
    return s[i];
}
char get_nearest_left_character(const string &s, int i){
    i-=1;
    while (s[i] == ' ' && i >= 0) i--;
    if (i == -1 || i == s.length()) {return ' ';}
    return s[i];
}


array<int,2> parse_array(const string &inProgram){

    array<int,2> point;
    for (char currCh : inProgram) {
        switch (currCh) {
            case ']':
                cout << currCh;
                return point;
        }
    }
    return point;
}

char get_precendence_operator(const string &S, char right_character, char left_character){
    if (precedence_map[left_character] < precedence_map[right_character]){
        return left_character;
    }else{
        return right_character;
    }
}

float lexer(const string &inProgram) {

    precedence_map.insert(pair<char, size_t> {'(',8});
    precedence_map.insert(pair<char, size_t> {')',9});
    precedence_map.insert(pair<char, size_t> {'*',3});
    precedence_map.insert(pair<char, size_t> {'/',4});
    precedence_map.insert(pair<char, size_t> {'+',5});
    precedence_map.insert(pair<char, size_t> {'-',6});
    precedence_map.insert(pair<char, size_t> {' ',7});

    vector<Term*> term_stack;
    
    Term *root_term, *current_term;

    size_t i = 0, length = inProgram.length();

    while (i < length){
        char current_char = inProgram[i];
        char right_char = get_nearest_right_character(inProgram, i);
        char left_char = get_nearest_left_character(inProgram, i);

        if (char_is_a_variable(current_char)){
            cout << char_is_an_operator(right_char) << endl;
            if (!(char_is_an_operator(right_char) || char_is_a_right_parenthesis(right_char))){
                cout<< "invalid equation : expected ) or an operator after " << current_char << ", recieved "  << right_char << " instead";
                // throw;
            }
            char point_to_char = get_precendence_operator(inProgram, right_char, left_char);
            cout << point_to_char << endl;
            BinaryOperator *parent = new BinaryOperator(point_to_char);
            Term *child = new Term(current_char);
            root_term = parent;
            term_stack.push_back(child);
        }
        if (char_is_a_left_parenthesis(current_char)){
            if (char_is_an_operator(right_char)){
                cout<< "invalid equation : expected (, ) or a variable after " << current_char << ", recieved "  << right_char << " instead";
                // throw;
            }
            Term *t = new Term(current_char);
            term_stack.push_back(t);
        }
        if (char_is_a_right_parenthesis(current_char)){
            if (char_is_a_variable(right_char)){
                cout<< "invalid equation : expected (, ) or an operator after " << current_char << ", recieved "  << right_char << " instead";
                // throw;
            }
            Term *t = new Term(current_char);
            term_stack.push_back(t);
        }
        if (char_is_an_operator(current_char)){
            if (!char_is_a_variable(right_char) and !char_is_a_left_parenthesis(right_char)){
                cout<< "invalid equation : expected ( or a variable after " << current_char << ", recieved "  << right_char << " instead";
                // throw;
            }
            Term *t = new Term(current_char);
            term_stack.push_back(t);
        }
        i++;
    }

    return root_term->get_value();
}

int main(){

    value_map.insert(pair<char, float> {'a', -1});
    value_map.insert(pair<char, float> {'b', 1});
    value_map.insert(pair<char, float> {'c', 0});

    // Parser *p1 = new Parser("p1");
    // Parser *p2 = new Parser("p2");
    // Parser *p3 = new Parser("p3");
    // Parser *p4 = new Parser("p4");
    
    // p1->append_child(p2);
    // p1->append_child(p3);

    // const string s = "hello";


    string test1 = "a*b + c";
    string test2 = "a*(b + c)";
    string test3 = "a * (b + c)";
    string test4 = "(a +b )* (b + c)";

    cout << "\n\nTest1\n";
    lexer(test1);
    cout << "\n\nTest2\n";
    lexer(test2);
    cout << "\n\nTest3\n";
    lexer(test3);
    cout << "\n\nTest4\n";
    lexer(test4);

    lexer ("a*b+c");
    return 0;
}