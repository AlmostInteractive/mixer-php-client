<?php

declare(strict_types=1);

namespace MixerApi\Api;

use GuzzleHttp\Client;
use GuzzleHttp\Exception\GuzzleException;
use GuzzleHttp\Psr7\Request;
use GuzzleHttp\RequestOptions;
use Psr\Http\Message\ResponseInterface;

abstract class AbstractApiBase
{
    protected $clientId;
    protected $guzzleClient;

    public function __construct(string $clientId, Client $guzzleClient)
    {
        $this->clientId = $clientId;
        $this->guzzleClient = $guzzleClient;
    }

    /**
     * @throws GuzzleException
     */
    protected function apiGet(string $uriEndpoint, array $queryParams = [], string $bearer = null): ResponseInterface
    {
        $headers = ['Client-ID' => $this->clientId];
        if ($bearer)
            $headers['Authorization'] = sprintf('Bearer %s', $bearer);

        $request = new Request(
            'GET',
            sprintf('%s%s', $uriEndpoint, $this->generateQueryParams($queryParams)),
            $headers
        );

        return $this->guzzleClient->send($request);
    }

    /**
     * @throws GuzzleException
     */
    protected function apiPost(string $uriEndpoint, ?array $body = null, string $bearer = null): ResponseInterface
    {
        $headers = ['Client-ID' => $this->clientId];
        if ($bearer)
            $headers['Authorization'] = sprintf('Bearer %s', $bearer);

        $request = new Request(
            'POST',
            $uriEndpoint,
            $headers);

        $options = $body
            ? [
                RequestOptions::JSON => $body
            ]
            : [];

        return $this->guzzleClient->send($request, $options);
    }

    /**
     * $queryParamsMap should be a mapping of the param key expected in the API call URL,
     * and the value to be sent for that key.
     *
     * [['key' => 'param_key', 'value' => 42],['key' => 'other_key', 'value' => 'asdf']]
     * would result in
     * ?param_key=42&other_key=asdf
     */
    protected function generateQueryParams(array $queryParams): string
    {
        $queryStringParams = '';
        foreach ($queryParams as $key => $value) {
            if ($value) {
                $format = is_int($value) ? '%d' : '%s';
                $queryStringParams .= sprintf('&%s=' . $format, $key, $value);
            }
        }

        return $queryStringParams ? '?' . substr($queryStringParams, 1) : '';
    }
}
