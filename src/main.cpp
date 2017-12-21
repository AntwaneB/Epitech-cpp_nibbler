#include <iostream>
#include "App.hpp"
#include "Exception.hpp"

int	main(int ac, char **av)
{
	srand(time(NULL));

	App*	app = NULL;

	try
	{
		app = new App(ac, av);

		int ret = app->run();
		delete app;

		return (ret);
	} catch (NoDeleteException const & e)
	{
		std::cerr << e.what() << std::endl;

		return (0);
	} catch (GraphicsException const & e)
	{
		std::cerr << e.what() << std::endl;

		return (0);
	}
	catch (ExitException const & e)
	{
		std::cerr << e.what() << std::endl;

		if (app)
			delete app;
		return (0);
	} catch (Exception const & e)
	{
		std::cerr << e.what() << std::endl;

		if (app)
			delete app;
		return (-1);
	}
	return (0);
}
