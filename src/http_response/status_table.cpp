/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_table.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:36:52 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/01/15 16:43:31 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv/HttpResponse.hpp"
#include <map>

const std::string& status_table(t_status_code code)
{
	static std::map<t_status_code, std::string> status;

	if (status.empty()) {
		status[INFO_CONTINUE] = "Info continue";
		status[INFO_SWITCHING_PROTOCOLS] = "Info switching protocols";
		status[INFO_PROCESSING] = "Info processing";
		status[INFO_EARLY_HINTS] = "Info early hints";

		status[SUCCESS_OK] = "Success ok";
		status[SUCCESS_CREATED] = "Success created";
		status[SUCCESS_ACCEPTED] = "Success accepted";
		status[SUCCESS_NOT_AUTHORITATIVE_INFORMATION] = "Success not authoritative information";
		status[SUCCESS_NO_CONTENT] = "Success no content";
		status[SUCCESS_RESET_CONTENT] = "Success reset content";
		status[SUCCESS_PARTIAL_CONTENT] = "Success partial content";
		status[SUCCESS_MULTI_STATUS] = "Success multi status";
		status[SUCCESS_ALREADY_REPORTED] = "Success already reported";
		status[SUCCESS_CONTENT_DIFFERENT] = "Success content different";
		status[SUCCESS_IM_USED] = "Success im used";

		status[REDIRECT_MULTIPLE_CHOICES] = "Redirect multiple choices";
		status[REDIRECT_MOVED_PERMANENTLY] = "Redirect moved permanently";
		status[REDIRECT_FOUND] = "Redirect found";
		status[REDIRECT_SEE_OTHER] = "Redirect see other";
		status[REDIRECT_NOT_MODIFIED] = "Redirect not modified";
		status[REDIRECT_USE_PROXY] = "Redirect use proxy";
		status[REDIRECT__UNUSED] = "Redirect  unused";
		status[REDIRECT_TEMPORARY_REDIRECT] = "Redirect temporary redirect";
		status[REDIRECT_PERMANENT_REDIRECT] = "Redirect permanent redirect";
		status[REDIRECT_TOO_MANY_REDIRECTS] = "Redirect too many redirects";

		status[HTTP_ERROR_BAD_REQUEST] = "Http error bad request";
		status[HTTP_ERROR_UNAUTHORIZED] = "Http error unauthorized";
		status[HTTP_ERROR_PAYMENT_REQUIRED] = "Http error payment required";
		status[HTTP_ERROR_FORBIDDEN] = "Http error forbidden";
		status[HTTP_ERROR_NOT_FOUND] = "Http error not found";
		status[HTTP_ERROR_METHOD_NOT_ALLOWED] = "Http error method not allowed";
		status[HTTP_ERROR_NOT_ACCEPTABLE] = "Http error not acceptable";
		status[HTTP_ERROR_PROXY_AUTH_REQUIRED] = "Http error proxy auth required";
		status[HTTP_ERROR_TIMEOUT] = "Http error timeout";
		status[HTTP_ERROR_CONFLICT] = "Http error conflict";
		status[HTTP_ERROR_GONE] = "Http error gone";
		status[HTTP_ERROR_LENGTH_REQUIRED] = "Http error length required";
		status[HTTP_ERROR_PRECOND_FAILED] = "Http error precond failed";
		status[HTTP_ERROR_REQUEST_ENTITY_TOO_LARGE] = "Http error request entity too large";
		status[HTTP_ERROR_REQUEST_URI_TOO_LON] = "Http error request uri too lon";
		status[HTTP_ERROR_UNSUPPORTED_MEDIA_TYPE] = "Http error unsupported media type";
		status[HTTP_ERROR_REQUESTED_RANGE_UNSATISFIABLE] = "Http error requested range unsatisfiable";
		status[HTTP_ERROR_EXPECTATION_FAILED] = "Http error expectation failed";
		status[HTTP_ERROR_I_AM_A_TEAPOT] = "Http error i am a teapot";
		status[HTTP_ERROR_PAGE_EXPIRED] = "Http error page expired";
		status[HTTP_ERROR_BAD_MAPPING_OR_MISDIRECTED_REQUEST] = "Http error bad mapping or misdirected request";
		status[HTTP_ERROR_UNPROCESSABLE_ENTITY] = "Http error unprocessable entity";
		status[HTTP_ERROR_LOCKED] = "Http error locked";
		status[HTTP_ERROR_METHOD_FAILURE] = "Http error method failure";
		status[HTTP_ERROR_TOO_EARLY] = "Http error too early";
		status[HTTP_ERROR_UPGRADE_REQUIRED] = "Http error upgrade required";
		status[HTTP_ERROR_INVALID_DIGITAL_SIG] = "Http error invalid digital sig";
		status[HTTP_ERROR_PRECOND_REQUIRED] = "Http error precond required";
		status[HTTP_ERROR_TOO_MANY_REQUESTS] = "Http error too many requests";
		status[HTTP_ERROR_REQUEST_HEADER_FIELDS_TOO_LARGE] = "Http error request header fields too large";
		status[HTTP_ERROR_RETRY_WITH] = "Http error retry with";
		status[HTTP_ERROR_BLOCKED_BY_WINDOWS_PARENTAL_CONTROL] = "Http error blocked by windows parental control";
		status[HTTP_ERROR_UNAVAILABLE_FOR_LEGAL_REASONS] = "Http error unavailable for legal reasons";
		status[HTTP_ERROR_UNRECOVERABLE_ERROR] = "Http error unrecoverable error";

		status[HTTP_ERROR_NO_RESPONSE] = "Http error no response";
		status[HTTP_ERROR_SSL_CERTIFICATE_ERROR] = "Http error SSL certificate error";
		status[HTTP_ERROR_SSL_CERTIFICATE_REQUIRED] = "Http error SSL certificate required";
		status[HTTP_ERROR_HTTP_REQUEST_SENT_TO_HTTPS_PORT] = "Http error http request sent to https port";
		status[HTTP_ERROR_TOKEN_EXPIRED_OR_INVALID] = "Http error token expired or invalid";
		status[HTTP_ERROR_CLIENT_CLOSED_REQUEST] = "Http error client closed request";

		status[SERVER_ERROR_INTERNAL_SERVER_ERROR] = "Server error internal server error";
		status[SERVER_ERROR_NOT_IMPLEMENTED] = "Server error not implemented";
		status[SERVER_ERROR_BAD_GATEWAY_OR_PROXY_ERROR] = "Server error bad gateway or proxy error";
		status[SERVER_ERROR_SERVICE_UNAVAILABLE] = "Server error service unavailable";
		status[SERVER_ERROR_GATEWAY_TIMEOUT] = "Server error gateway timeout";
		status[SERVER_ERROR_HTTP_VERSION_NOT_SUPPORTED] = "Server error http version not supported";
		status[SERVER_ERROR_VARIANT_ALSO_NEGOTIATE] = "Server error variant also negotiate";
		status[SERVER_ERROR_INSUFFICIENT_STORAGE] = "Server error insufficient storage";
		status[SERVER_ERROR_LOOP_DETECTED] = "Server error loop detected";
		status[SERVER_ERROR_BANDWITH_LIMIT_EXCEEDED] = "Server error bandwith limit exceeded";
		status[SERVER_ERROR_NOT_EXTENDED] = "Server error not extended";
		status[SERVER_ERROR_NETWORK_AUTH_REQUIRED] = "Server error network auth required";
	}
	return status[code];
}
