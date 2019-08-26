<?php

declare(strict_types=1);

namespace MixerApi\Api;

use GuzzleHttp\Client;
use GuzzleHttp\Exception\GuzzleException;
use GuzzleHttp\Psr7\Request;
use GuzzleHttp\RequestOptions;
use Psr\Http\Message\ResponseInterface;

class OauthApi extends AbstractApiBase
{
    private const AUTH_ENDPOINT = 'https://mixer.com/oauth/authorize';

    private $clientId;
    private $clientSecret;

    public function __construct(string $clientId, string $clientSecret, Client $guzzleClient)
    {
        parent::__construct($guzzleClient);
        $this->clientId = $clientId;
        $this->clientSecret = $clientSecret;
    }

    /**
     * @return string A full authentication URL, including the Guzzle client's base URI.
     */
    public function getAuthUrl(string $redirectUri, string $responseType = 'code', string $scope = '', bool $forceVerify = false, string $state = null): string
    {
        return sprintf(
            '%s%s',
            self::AUTH_ENDPOINT,
            $this->getPartialAuthUrl($redirectUri, $responseType, $scope, $forceVerify, $state)
        );
    }

    /**
     * @throws GuzzleException
     */
    public function getUserAccessToken(string $code, string $redirectUri): ResponseInterface
    {
        return $this->makeRequest(
            new Request('POST', 'oauth/token'),
            [
                RequestOptions::JSON => [
                    'client_id' => $this->clientId,
                    'client_secret' => $this->clientSecret,
                    'grant_type' => 'authorization_code',
                    'redirect_uri' => $redirectUri,
                    'code' => $code
                ]
            ]
        );
    }

    /**
     * @throws GuzzleException
     */
    public function refreshToken(string $refeshToken, string $scope = ''): ResponseInterface
    {
        $requestOptions = [
            'client_id' => $this->clientId,
            'client_secret' => $this->clientSecret,
            'grant_type' => 'refresh_token',
            'refresh_token' => $refeshToken,
        ];
        if ($scope) {
            $requestOptions['scope'] = $scope;
        }

        return $this->makeRequest(
            new Request('POST', 'oauth/token'),
            [
                RequestOptions::JSON => $requestOptions
            ]
        );
    }

    /**
     * @throws GuzzleException
     */
    public function isValidAccessToken(string $accessToken): bool
    {
        $response = $this->makeRequest(
            new Request(
                'POST',
                'oauth/token/introspect',
                [],
                json_encode(['token' => $accessToken])
            )
        );
        $data = json_decode($response->getBody()->getContents(), true);
        return $data['active'] === true;
    }

    /**
     * @throws GuzzleException
     */
    public function getAppAccessToken(string $scope = ''): ResponseInterface
    {
        return $this->makeRequest(
            new Request('POST', 'oauth/token'),
            [
                RequestOptions::JSON => [
                    'client_id' => $this->clientId,
                    'client_secret' => $this->clientSecret,
                    'grant_type' => 'client_credentials',
                    'scope' => $scope,
                ]
            ]
        );
    }

    /**
     * @throws GuzzleException
     */
    private function makeRequest(Request $request, array $options = []): ResponseInterface
    {
        return $this->guzzleClient->send($request, $options);
    }

    /**
     * @return string A partial authentication URL, excluding the Guzzle client's base URI.
     */
    private function getPartialAuthUrl(string $redirectUri, string $responseType = 'code', string $scope = '', bool $forceVerify = false, string $state = null): string
    {
        $optionalParameters = '';
        $optionalParameters .= $forceVerify ? '&approval_prompt=force' : '';
        $optionalParameters .= $state ? sprintf('&state=%s', $state) : '';

        return sprintf(
            '?client_id=%s&redirect_uri=%s&response_type=%s&scope=%s%s',
            $this->clientId,
            $redirectUri,
            $responseType,
            $scope,
            $optionalParameters
        );
    }
}
