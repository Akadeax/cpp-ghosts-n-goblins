#include "pch.h"
#include "ConditionalTransition.h"

ConditionalTransition::ConditionalTransition(
	std::string origin,
	std::string destination,
	std::unordered_map<std::string, int> conditions
) : AnimatorTransition(origin, destination)
{
	m_Conditions = conditions;
}

ConditionalTransition::~ConditionalTransition()
{
}

bool ConditionalTransition::ShouldTransition()
{
	for (auto& pair : m_Conditions)
	{
		if (m_pAnimator->GetParameter(pair.first) == pair.second) continue;
		else return false;
	}

	return true;
}
