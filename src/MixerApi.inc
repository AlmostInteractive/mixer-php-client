<?php

declare(strict_types=1);

namespace MixerApi;

use GuzzleHttp\Client;
use MixerApi\Api\OauthApi;
use MixerApi\Api\UsersApi;

class MixerApi
{
    private $oauthApi;
    private $usersApi;

    public function __construct(string $clientId, string $clientSecret, Client $guzzleClient = null)
    {
        $guzzleClient = $guzzleClient ?? new MixerGuzzleClient($clientId);

        $this->oauthApi = new OauthApi($clientId, $clientSecret, $guzzleClient);
        $this->usersApi = new UsersApi($guzzleClient);
    }

    public function getOauthApi(): OauthApi { return $this->oauthApi; }
    public function getusersApi(): UsersApi { return $this->usersApi; }
}
