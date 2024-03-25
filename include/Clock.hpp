#pragma once


namespace kn
{
	class Clock final
	{
	public:
		Clock() = default;
		~Clock() = default;

		double tick();

	private:
		double deltaTime = 0.0;
		double last = 0.0;
		double now = 0.0;
	};
}