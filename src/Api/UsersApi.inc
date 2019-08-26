<?php

declare(strict_types=1);

namespace MixerApi\Api;

use GuzzleHttp\Client;
use GuzzleHttp\Exception\GuzzleException;
use GuzzleHttp\Psr7\Request;
use GuzzleHttp\RequestOptions;
use Psr\Http\Message\ResponseInterface;


class UsersApi extends AbstractApiBase
{
    /**
     * @throws GuzzleException
     */
    public function getUserByAccessToken(string $accessToken): ResponseInterface
    {
        return $this->apiGet('users/current', [], $accessToken);
    }
}
