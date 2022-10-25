// OstEngine (c) - Kasper Esbjornsson 2022

#pragma once

namespace ost
{
	enum class ELogVerbosity
	{
		Verbose, // A message that can most likely be ignored for most purposes
		Log,	 // A message that provides a somewhat useful insight into what is happening
		Confirm, // Confirmation that something is set up as intended
		Warning, // A warning that something unexpected might have happened
		Error,	 // Something went absolutely tits up
	};
}