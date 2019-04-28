

class LoadableClass {
private :
	int i;

public :
	LoadableClass ();
	~LoadableClass ();

	void doSomething ();
	int doSum (int a, int b);


	typedef LoadableClass* create_t	();
};