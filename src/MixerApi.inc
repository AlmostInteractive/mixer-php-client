<?php

/*
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 *
 * https://github.com/AlmostInteractive/mixer-php-client
 */

declare(strict_types=1);

namespace MixerApi;

use GuzzleHttp\Client;
use MixerApi\Api\ChannelsApi;
use MixerApi\Api\OauthApi;
use MixerApi\Api\UsersApi;

class MixerApi
{
    private $oauthApi;
    private $usersApi;
    private $channelsApi;

    public function __construct(string $clientId, string $clientSecret, Client $guzzleClient = null)
    {
        $guzzleClient = $guzzleClient ?? new MixerGuzzleClient($clientId);

        $this->oauthApi = new OauthApi($clientId, $clientSecret, $guzzleClient);
        $this->usersApi = new UsersApi($clientId, $guzzleClient);
        $this->channelsApi = new ChannelsApi($clientId, $guzzleClient);
    }

    public function getOauthApi(): OauthApi { return $this->oauthApi; }
    public function getUsersApi(): UsersApi { return $this->usersApi; }
    public function getChannelsApi(): ChannelsApi { return $this->channelsApi; }
}
