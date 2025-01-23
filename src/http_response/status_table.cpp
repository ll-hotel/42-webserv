/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_table.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:36:52 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/01/15 17:43:51 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/HttpResponse.hpp"
#include <map>

const std::string& status_table(t_status_code code)
{
	static std::map<t_status_code, std::string> status;

	if (status.empty()) {
		status[INFO_CONTINUE] = "Continue";
		status[INFO_SWITCHING_PROTOCOLS] = "Switching protocols";
		status[INFO_PROCESSING] = "Processing";
		status[INFO_EARLY_HINTS] = "Early hints";

		status[SUCCESS_OK] = "Ok";
		status[SUCCESS_CREATED] = "Created";
		status[SUCCESS_ACCEPTED] = "Accepted";
		status[SUCCESS_NOT_AUTHORITATIVE_INFORMATION] = "Not authoritative information";
		status[SUCCESS_NO_CONTENT] = "No content";
		status[SUCCESS_RESET_CONTENT] = "Reset content";
		status[SUCCESS_PARTIAL_CONTENT] = "Partial content";
		status[SUCCESS_MULTI_STATUS] = "Multi status";
		status[SUCCESS_ALREADY_REPORTED] = "Already reported";
		status[SUCCESS_CONTENT_DIFFERENT] = "Content different";
		status[SUCCESS_IM_USED] = "Im used";

		status[REDIRECT_MULTIPLE_CHOICES] = "Multiple choices";
		status[REDIRECT_MOVED_PERMANENTLY] = "Moved permanently";
		status[REDIRECT_FOUND] = "Found";
		status[REDIRECT_SEE_OTHER] = "See other";
		status[REDIRECT_NOT_MODIFIED] = "Not modified";
		status[REDIRECT_USE_PROXY] = "Use proxy";
		status[REDIRECT__UNUSED] = " unused";
		status[REDIRECT_TEMPORARY_REDIRECT] = "Temporary redirect";
		status[REDIRECT_PERMANENT_REDIRECT] = "Permanent redirect";
		status[REDIRECT_TOO_MANY_REDIRECTS] = "Too many redirects";

		status[HTTP_ERROR_BAD_REQUEST] = "Bad request";
		status[HTTP_ERROR_UNAUTHORIZED] = "Unauthorized";
		status[HTTP_ERROR_PAYMENT_REQUIRED] = "Payment required";
		status[HTTP_ERROR_FORBIDDEN] = "Forbidden";
		status[HTTP_ERROR_NOT_FOUND] = "Not found";
		status[HTTP_ERROR_METHOD_NOT_ALLOWED] = "Method not allowed";
		status[HTTP_ERROR_NOT_ACCEPTABLE] = "Not acceptable";
		status[HTTP_ERROR_PROXY_AUTH_REQUIRED] = "Proxy auth required";
		status[HTTP_ERROR_TIMEOUT] = "Timeout";
		status[HTTP_ERROR_CONFLICT] = "Conflict";
		status[HTTP_ERROR_GONE] = "Gone";
		status[HTTP_ERROR_LENGTH_REQUIRED] = "Length required";
		status[HTTP_ERROR_PRECOND_FAILED] = "Precond failed";
		status[HTTP_ERROR_REQUEST_ENTITY_TOO_LARGE] = "Request entity too large";
		status[HTTP_ERROR_REQUEST_URI_TOO_LONG] = "Request uri too long";
		status[HTTP_ERROR_UNSUPPORTED_MEDIA_TYPE] = "Unsupported media type";
		status[HTTP_ERROR_REQUESTED_RANGE_UNSATISFIABLE] = "Requested range unsatisfiable";
		status[HTTP_ERROR_EXPECTATION_FAILED] = "Expectation failed";
		status[HTTP_ERROR_I_AM_A_TEAPOT] = "I am a teapot";
		status[HTTP_ERROR_PAGE_EXPIRED] = "Page expired";
		status[HTTP_ERROR_BAD_MAPPING_OR_MISDIRECTED_REQUEST] = "Bad mapping or misdirected request";
		status[HTTP_ERROR_UNPROCESSABLE_ENTITY] = "Unprocessable entity";
		status[HTTP_ERROR_LOCKED] = "Locked";
		status[HTTP_ERROR_METHOD_FAILURE] = "Method failure";
		status[HTTP_ERROR_TOO_EARLY] = "Too early";
		status[HTTP_ERROR_UPGRADE_REQUIRED] = "Upgrade required";
		status[HTTP_ERROR_INVALID_DIGITAL_SIG] = "Invalid digital sig";
		status[HTTP_ERROR_PRECOND_REQUIRED] = "Precond required";
		status[HTTP_ERROR_TOO_MANY_REQUESTS] = "Too many requests";
		status[HTTP_ERROR_REQUEST_HEADER_FIELDS_TOO_LARGE] = "Request header fields too large";
		status[HTTP_ERROR_RETRY_WITH] = "Retry with";
		status[HTTP_ERROR_BLOCKED_BY_WINDOWS_PARENTAL_CONTROL] = "Blocked by windows parental control";
		status[HTTP_ERROR_UNAVAILABLE_FOR_LEGAL_REASONS] = "Unavailable for legal reasons";
		status[HTTP_ERROR_UNRECOVERABLE_ERROR] = "Unrecoverable error";

		status[HTTP_ERROR_NO_RESPONSE] = "No response";
		status[HTTP_ERROR_SSL_CERTIFICATE_ERROR] = "sSL certificate error";
		status[HTTP_ERROR_SSL_CERTIFICATE_REQUIRED] = "sSL certificate required";
		status[HTTP_ERROR_HTTP_REQUEST_SENT_TO_HTTPS_PORT] = "Http request sent to https port";
		status[HTTP_ERROR_TOKEN_EXPIRED_OR_INVALID] = "Token expired or invalid";
		status[HTTP_ERROR_CLIENT_CLOSED_REQUEST] = "Client closed request";

		status[SERVER_ERROR_INTERNAL_SERVER_ERROR] = "Internal server error";
		status[SERVER_ERROR_NOT_IMPLEMENTED] = "Not implemented";
		status[SERVER_ERROR_BAD_GATEWAY_OR_PROXY_ERROR] = "Bad gateway or proxy error";
		status[SERVER_ERROR_SERVICE_UNAVAILABLE] = "Service unavailable";
		status[SERVER_ERROR_GATEWAY_TIMEOUT] = "Gateway timeout";
		status[SERVER_ERROR_HTTP_VERSION_NOT_SUPPORTED] = "Http version not supported";
		status[SERVER_ERROR_VARIANT_ALSO_NEGOTIATE] = "Variant also negotiate";
		status[SERVER_ERROR_INSUFFICIENT_STORAGE] = "Insufficient storage";
		status[SERVER_ERROR_LOOP_DETECTED] = "Loop detected";
		status[SERVER_ERROR_BANDWITH_LIMIT_EXCEEDED] = "Bandwith limit exceeded";
		status[SERVER_ERROR_NOT_EXTENDED] = "Not extended";
		status[SERVER_ERROR_NETWORK_AUTH_REQUIRED] = "Network auth required";
	}
	return status[code];
}
