<?php

declare(strict_types=1);

namespace MixerApi\Api;

use GuzzleHttp\Client;
use GuzzleHttp\Exception\GuzzleException;
use GuzzleHttp\Psr7\Request;
use GuzzleHttp\RequestOptions;
use Psr\Http\Message\ResponseInterface;


class ChannelsApi extends AbstractApiBase
{
    /**
     * @throws GuzzleException
     * https://dev.mixer.com/rest/index.html#channels__channelIdOrToken__get
     */
    public function getChannel(string $channelIdOrAccessToken): ResponseInterface
    {
        return $this->apiGet("channels/$channelIdOrAccessToken");
    }

    /**
     * @throws GuzzleException
     * https://dev.mixer.com/rest/index.html#channels__channelIdOrToken__details_get
     */
    public function getChannelDetails(string $channelIdOrAccessToken): ResponseInterface
    {
        return $this->apiGet("channels/$channelIdOrAccessToken/details");
    }

    /**
     * @throws GuzzleException
     * https://dev.mixer.com/rest/index.html#channels__channelId__follow_get
     */
    public function getFollowers(string $channelId, ?int $from = null, ?int $to = null): ResponseInterface
    {
        $queryParams = [];

        if ($from !== null)
            $queryParams['from'] = $from;
        else
            $queryParams['from'] = date('c');

        if ($to !== null)
            $queryParams['to'] = $to;

        return $this->apiGet("channels/$channelId/analytics/tsdb/followers", $queryParams);
    }

    /**
     * @throws GuzzleException
     * https://dev.mixer.com/rest/index.html#channels__channelId__recordings_get
     */
    public function getRecordings(string $channelId, ?int $page = null, ?int $limit = null, ?string $where = null, ?string $fields = null): ResponseInterface
    {
        $queryParams = [];

        if ($page !== null)
            $queryParams['page'] = $page;
        if ($page !== null)
            $queryParams['limit'] = $limit;
        if ($page !== null)
            $queryParams['where'] = $where;
        if ($page !== null)
            $queryParams['fields'] = $fields;

        return $this->apiGet("channels/$channelId/recordings", $queryParams);
    }
}
