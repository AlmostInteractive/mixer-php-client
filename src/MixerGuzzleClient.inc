<?php

declare(strict_types=1);

namespace MixerClient;

use GuzzleHttp\Client;

class MixerGuzzleClient extends Client
{
    private const BASE_URI = 'https://mixer.com/api/v1/';

    public function __construct(string $clientId, array $config = [])
    {
        parent::__construct($config + [
                'base_uri' => self::BASE_URI,
                'timeout' => 30,
                'headers' => ['Client-ID' => $clientId, 'Content-Type' => 'application/json'],
            ]);
    }
}
