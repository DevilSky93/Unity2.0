#pragma once


namespace ESGI {
	struct EngineContext
	{
		// l'utilisation de references dans EngineContext nous permet d'utiliser une syntaxe proche du C#
		struct Clock& clock;
		struct Input& input;
		struct Engine& engine;

		EngineContext(Clock& c, Input& i, Engine& e) : clock(c), input(i), engine(e) {}
		~EngineContext() { /*mettez un breakpoint histoire de s'assurer que l'objet est bien detruit*/ }

		Clock& Clock() const;
		Input& Input() const;
		Engine& Engine() const;
	};
}
