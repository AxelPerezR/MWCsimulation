#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{
	//El primer nombre es la funcion, el segundo lo ponemos nosotros
	MyPrimaryGenerator *generator = new MyPrimaryGenerator();
	SetUserAction(generator);
	
	MyRunAction *runAction = new MyRunAction();
	SetUserAction(runAction);
}
