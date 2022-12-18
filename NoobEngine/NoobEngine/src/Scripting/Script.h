#pragma once

namespace NoobEngine { namespace Script {
	
	class Script
	{
	private:
	
	public:
		virtual void Init() = 0;
		virtual void Update(float _deltatime) = 0;
		virtual void Terminate() = 0;
	};

	class ControllerScript : public Script
	{
	public:
		void Init() override;
		void Update(float _deltatime) override;
		void Terminate() override;
	};

}}