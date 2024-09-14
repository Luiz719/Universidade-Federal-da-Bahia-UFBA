// prettypring API

void print_decl(struct decl *d);
void print_stmt(struct stmt *st);
void print_type(struct type *type);
void print_params(struct param_list *pl);
void print_var(struct decl *var);
void print_array(struct decl *array);
void print_func(struct decl *f);
void print_bexpr(char *c, struct expr *l, struct expr *r);
void print_expr(struct expr *e);
void print_name(char *name);

void bracket(struct decl *program);


