#pragma once

#include "InfraStructure.h"

namespace ESGI
{
	// "forward declaration" d'une structure qui elle meme reference des classes
	// qui ne sont pas encore definies (fonctionne ici car il s'agit de pointeurs,
	// seul le typage interesse le compilateur dans ce cas)	
	struct EngineContext;

	struct Engine : public InfraStructure
	{
		// Un exemple basique de sous-systeme du moteur (par ex. le moteur Behaviour)
		struct EngineSystem
		{
			double targetFrameRate = 1.0 / 60.0;
			double accumulatedTime = 0.0;
			int maxIterations = 2;

			bool Create() { return true; }
			void Destroy() {}
			bool Initialize() { return true; }
			void DeInitialize() {}
			void Update(float deltaTime) {}
			void FixedUpdate(float deltaTime) {}
		};

		// simple exemple, ou alors un vector ou une liste simplement chainee (intrusive) de systems
		EngineSystem* m_AIEngine;


		void ProcessSystems(double elapsedTime);

		// ---

		bool Initialize() final;

		void DeInitialize() final;

		// ce n'est pas une fonction virtuelle !
		void Update(EngineContext& context);

	};
}
