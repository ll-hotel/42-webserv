/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:04:35 by ll-hotel          #+#    #+#             */
/*   Updated: 2025/01/15 17:34:36 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP
#include "webserv/HttpRequest.hpp"
#include <string>

typedef enum {
        INFO_CONTINUE = 100,
        INFO_SWITCHING_PROTOCOLS = 101,
        INFO_PROCESSING = 102,
        INFO_EARLY_HINTS = 103,

        SUCCESS_OK = 200,
        SUCCESS_CREATED = 201,
        SUCCESS_ACCEPTED = 202,
        SUCCESS_NOT_AUTHORITATIVE_INFORMATION = 203,
        SUCCESS_NO_CONTENT = 204,
        SUCCESS_RESET_CONTENT = 205,
        SUCCESS_PARTIAL_CONTENT = 206,
        SUCCESS_MULTI_STATUS = 207,
        SUCCESS_ALREADY_REPORTED = 208,
        SUCCESS_CONTENT_DIFFERENT = 210,
        SUCCESS_IM_USED = 226,

        REDIRECT_MULTIPLE_CHOICES = 300,
        REDIRECT_MOVED_PERMANENTLY = 301,
        REDIRECT_FOUND = 302,
        REDIRECT_SEE_OTHER = 303,
        REDIRECT_NOT_MODIFIED = 304,
        REDIRECT_USE_PROXY = 305,
        REDIRECT__UNUSED = 306,
        REDIRECT_TEMPORARY_REDIRECT = 307,
        REDIRECT_PERMANENT_REDIRECT = 308,
        REDIRECT_TOO_MANY_REDIRECTS = 310,

        HTTP_ERROR_BAD_REQUEST = 400,
        HTTP_ERROR_UNAUTHORIZED = 401,
        HTTP_ERROR_PAYMENT_REQUIRED = 402,
        HTTP_ERROR_FORBIDDEN = 403,
        HTTP_ERROR_NOT_FOUND = 404,
        HTTP_ERROR_METHOD_NOT_ALLOWED = 405,
        HTTP_ERROR_NOT_ACCEPTABLE = 406,
        HTTP_ERROR_PROXY_AUTH_REQUIRED = 407,
        HTTP_ERROR_TIMEOUT = 408,
        HTTP_ERROR_CONFLICT = 409,
        HTTP_ERROR_GONE = 410,
        HTTP_ERROR_LENGTH_REQUIRED = 411,
        HTTP_ERROR_PRECOND_FAILED = 412,
        HTTP_ERROR_REQUEST_ENTITY_TOO_LARGE = 413,
        HTTP_ERROR_REQUEST_URI_TOO_LONG = 414,
        HTTP_ERROR_UNSUPPORTED_MEDIA_TYPE = 415,
        HTTP_ERROR_REQUESTED_RANGE_UNSATISFIABLE = 416,
        HTTP_ERROR_EXPECTATION_FAILED = 417,
        HTTP_ERROR_I_AM_A_TEAPOT = 418,
        HTTP_ERROR_PAGE_EXPIRED = 419,
        HTTP_ERROR_BAD_MAPPING_OR_MISDIRECTED_REQUEST = 421,
        HTTP_ERROR_UNPROCESSABLE_ENTITY = 422,
        HTTP_ERROR_LOCKED = 423,
        HTTP_ERROR_METHOD_FAILURE = 424,
        HTTP_ERROR_TOO_EARLY = 425,
        HTTP_ERROR_UPGRADE_REQUIRED = 426,
        HTTP_ERROR_INVALID_DIGITAL_SIG = 427,
        HTTP_ERROR_PRECOND_REQUIRED = 428,
        HTTP_ERROR_TOO_MANY_REQUESTS = 429,
        HTTP_ERROR_REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
        HTTP_ERROR_RETRY_WITH = 449,
        HTTP_ERROR_BLOCKED_BY_WINDOWS_PARENTAL_CONTROL = 450,
        HTTP_ERROR_UNAVAILABLE_FOR_LEGAL_REASONS = 451,
        HTTP_ERROR_UNRECOVERABLE_ERROR = 456,

        HTTP_ERROR_NO_RESPONSE = 444,
        HTTP_ERROR_SSL_CERTIFICATE_ERROR = 495,
        HTTP_ERROR_SSL_CERTIFICATE_REQUIRED = 496,
        HTTP_ERROR_HTTP_REQUEST_SENT_TO_HTTPS_PORT = 497,
        HTTP_ERROR_TOKEN_EXPIRED_OR_INVALID = 498,
        HTTP_ERROR_CLIENT_CLOSED_REQUEST = 499,

        SERVER_ERROR_INTERNAL_SERVER_ERROR = 500,
        SERVER_ERROR_NOT_IMPLEMENTED = 501,
        SERVER_ERROR_BAD_GATEWAY_OR_PROXY_ERROR = 502,
        SERVER_ERROR_SERVICE_UNAVAILABLE = 503,
        SERVER_ERROR_GATEWAY_TIMEOUT = 504,
        SERVER_ERROR_HTTP_VERSION_NOT_SUPPORTED = 505,
        SERVER_ERROR_VARIANT_ALSO_NEGOTIATE = 506,
        SERVER_ERROR_INSUFFICIENT_STORAGE = 507,
        SERVER_ERROR_LOOP_DETECTED = 508,
        SERVER_ERROR_BANDWITH_LIMIT_EXCEEDED = 509,
        SERVER_ERROR_NOT_EXTENDED = 510,
        SERVER_ERROR_NETWORK_AUTH_REQUIRED = 511,
} t_status_code;

const std::string &status_table(t_status_code code);

class HttpResponse
{
private:
        t_status_code _status_code;
        std::string _file;

public:
        HttpResponse();
        HttpResponse(const HttpResponse &);
        HttpResponse(const HttpRequest &request);
        ~HttpResponse();
        HttpResponse &operator=(const HttpResponse &);

        std::string generate();
};

#endif
