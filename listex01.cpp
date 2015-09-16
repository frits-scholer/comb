#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define root col_array[0]

using namespace std;

const size_t max_level=100;
const size_t max_degree=40;

class column;

class node {
  node *left, *right;
  node *up, *down;
  column *col;
public:
  node():up(this),down(this){}
  node *getleft() {return left;}
  node *getright() {return right;}
  node *getup() {return up;}
  node *getdown() {return down;}
  column *getcol() {return col;}
  void setleft(node *n) {left = n;}
  void setright( node *n) {right = n;}
  void setup( node *n) {up = n;}
  void setdown( node *n) {down = n;}
  void setcol( column *c) {col = c;}
  friend void print_row(node*);
  friend void cover(column*);
  friend void uncover(column*);
};

class column {
  node head;
  size_t len;
  string _name;
  column *prev, *next;
public:
  column(const char * nm = ""): _name(nm), len(0), prev(nullptr),next(nullptr) {}
  bool operator==(const column& rhs) { return _name == rhs._name;}
  const string name() {return _name;}
  const column *getnext() {return next;}
  void setnext(column *c) {next = c;}
  const column *getprev() {return prev;}
  void setprev(column *c) {prev = c;}
  node& gethead() {return head;}
  size_t getlen() {return len;}
  void setlen(size_t l) {len = l;}
  void print_column() const { cout << _name << " :" << len << endl;}
  friend void print_row(node*);
  friend void cover(column*);
  friend void uncover(column*);
};

void print_row(node *p) {
  node*q = p;
  int k;
  do {
    cout << " " << q->col->_name;
    q = q->right;
  } while(q != p);
  cout << "\n";
}

void cover(column *c) {
  register column*l,*r;
  register node*rr,*nn,*uu,*dd;
  register int k = 1;
  l= c->prev;
  r= c->next;
  l->next= r;
  r->prev= l;
  for (rr = c->head.down;rr != &(c->head);rr = rr->down)
    for(nn= rr->right;nn!=rr;nn= nn->right) {
      uu = nn->up;
      dd = nn->down;
      uu->down = dd;
      dd->up = uu;
      k++;
      nn->col->len--;
    }
}

void uncover(column *c) {
  register column *l, *r;
  register node *rr, *nn, *uu, *dd;
  for (rr = c->head.up;rr!=&(c->head);rr= rr->up)
    for (nn= rr->left;nn!=rr;nn= nn->left) {
      uu = nn->up;
      dd = nn->down;
      uu->down = dd->up = nn;
      nn->col->len++;
    }
  l = c->prev;
  r = c->next;
  l->next = r->prev = c;
}

int main () {
  bool primary = true;
  vector<column*>::iterator cci;
  vector<column*> col_array;
  vector<node *> node_array;
  vector<node*>::iterator cni;
  column *cur_col;
  node *cur_node;
  string strbuf;
  col_array.push_back(new column());
  //read in the data structures
  //read the columns
  getline(cin,strbuf);
  istringstream is(strbuf);
  char col_name[8];
  while (!is.eof()) {
    is >> col_name;
    if (col_name[0] == '|') {
      primary = false;
      col_array.back()->setnext(root);
      root->setprev(*(prev(col_array.end()))); 
      continue;
    }
    col_array.push_back(new column(col_name));
    cci = prev(col_array.end());
    cur_col = *cci;
    if (primary) {
      cur_col->setprev(*(prev(cci)));
      (*(prev(cci)))->setnext(cur_col);
    }
    else {
      cur_col->setnext(cur_col);
      cur_col->setprev(cur_col);
    }
  }
  if (primary) {
    cur_col = *(prev(col_array.end()));
    cur_col->setnext(root);
    root->setprev(cur_col);
  }
  //read the rows
  while (getline(cin,strbuf) && strbuf.length()>0) {
    is.clear();
    is.str(strbuf);
    node *row_start = nullptr;
    while (!is.eof()) {
      is >> col_name;
      //find the column
      column dummy(col_name);
      for (cci=col_array.begin();cci != col_array.end();++cci) {
	if (*(*cci)==dummy) break;
      }
      if (cci == col_array.end()) {cerr << "unknown column\n"; return 1;}
      //else { cout << col_name << "=";(*cci)->print_column();}
      cur_col = *cci;
      node_array.push_back(new node());
      cni = prev(node_array.end());
      cur_node = *cni;
      if (!row_start) {row_start = cur_node;}
      else {
	cur_node->setleft(*(prev(cni)));
	(*(prev(cni)))->setright(cur_node);
      }
      cur_node->setcol(cur_col);
      cur_node->setup(cur_col->gethead().getup());
      cur_col->gethead().getup()->setdown(cur_node);
      cur_col->gethead().setup(cur_node);
      cur_node->setdown( &(cur_col->gethead()));
      cur_col->setlen((cur_col->getlen())+1);
    }
    if (!row_start) {std::cerr << "Empty row\n";return 1;}
    row_start->setleft(cur_node);
    cur_node->setright(row_start);
    //test rows
    print_row(cur_node);
 }
  //test columns
  /* 
  for (cci = col_array.begin();cci != col_array.end();++cci) {
    (*cci)->print_column();
  }
  */

}
