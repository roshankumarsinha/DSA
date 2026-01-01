// Design Twitter

// Description:
// Design a simplified version of Twitter where users can post tweets, follow/unfollow another user,
// and is able to see the 10 most recent tweets in the user's news feed.

// Implement the Twitter class:
// 1. Twitter() Initializes your twitter object.
// 2. void postTweet(int userId, int tweetId) Composes a new tweet with ID tweetId by the user userId.
// 3. List<Integer> getNewsFeed(int userId) Retrieves the 10 most recent tweet IDs in the user's news feed.
//    Each item in the news feed must be posted by users who the user followed or by the user themselves.
//    Tweets must be ordered from most recent to least recent.
// 4. void follow(int followerId, int followeeId) The user with ID followerId started following the user with ID followeeId.
// 5. void unfollow(int followerId, int followeeId) The user with ID followerId started unfollowing the user with ID followeeId.

// Video Explanation : https://www.youtube.com/watch?v=iV_8CTkwA1o

// Approach using Unordered Map and Vector:
// 1. Use an unordered map to maintain a mapping of userId to a set of followees. This unordered map will also include 0 or 1,
//    where 0 indicates it is being unfollowed and 1 indicates it is being followed.
// 2. Data structure will look like: unordered_map<int, unordered_map<int, int>> followers; where the key is followerId and
//    the value is another unordered_map where key is followeeId and value is 0 or 1. 0 means unfollowed and 1 means followed.
// 3. Use vector of pairs to maintain the tweets. Each pair will contain tweetId and userId.
// 4. Data structure will look like: vector<pair<int, int>> tweets; where each pair contains tweetId and userId.
// 5. For postTweet, simply push the tweetId and userId as a pair into the tweets vector.
// 6. Why a vector for tweets?
//    Because we need to maintain the order of tweets as they are posted. The most recent tweet will be at the end of the vector.
// 7. For getNewsFeed, iterate the tweets vector from the end to the beginning and check if the tweet's userId is either the userId itself or
//    if the userId is followed by the userId. If yes, add the tweetId to the result vector until we have 10 tweets.
// 8. For follow, simply set the value of followeeId in the followers unordered_map to 1 for the given followerId.
// 9. For unfollow, set the value of followeeId in the followers unordered_map to 0 for the given followerId.

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Twitter {

  private:
    unordered_map<int, unordered_map<int, int>> followers; // followerId -> (followeeId -> 0/1), 0 means unfollowed, 1 means followed
    vector<pair<int, int>> tweets; // (tweetId, userId), maintains the order of tweets, most recent at the end of the vector

  public:
    Twitter() {
        // Constructor
    }

    void postTweet(int userId, int tweetId) {
        tweets.push_back({tweetId, userId}); // Add the tweet to the tweets vector, storing tweetId and userId
    }

    vector<int> getNewsFeed(int userId) {
        vector<int> newsFeed; // Result vector to store the 10 most recent tweet IDs
        for (int i = tweets.size() - 1; i >= 0 && newsFeed.size() < 10; i--) {  // Iterate from the end of tweets vector to get most recent tweets, limit to 10 tweets
            int tweetUserId = tweets[i].second; // Get the userId of the tweet
            // Check if the tweet is by the user themselves or by a followed user
            if (tweetUserId == userId || (followers[userId][tweetUserId] == 1)) {
                newsFeed.push_back(tweets[i].first); // Add tweetId to newsFeed
            }
        }
        return newsFeed; // Return the news feed
    }

    void follow(int followerId, int followeeId) {
        followers[followerId][followeeId] = 1; // Set followeeId as followed for followerId
    }

    void unfollow(int followerId, int followeeId) {
        followers[followerId][followeeId] = 0; // Set followeeId as unfollowed for followerId
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
int main() {
    Twitter* twitter = new Twitter();

    twitter->postTweet(1, 5);
    vector<int> feed1 = twitter->getNewsFeed(1); // Should return [5]
    for (int tweetId : feed1) {
        cout << tweetId << " ";
    }
    cout << endl;

    twitter->follow(1, 2);
    twitter->postTweet(2, 6);
    vector<int> feed2 = twitter->getNewsFeed(1); // Should return [6, 5]
    for (int tweetId : feed2) {
        cout << tweetId << " ";
    }
    cout << endl;

    twitter->unfollow(1, 2);
    vector<int> feed3 = twitter->getNewsFeed(1); // Should return [5]
    for (int tweetId : feed3) {
        cout << tweetId << " ";
    }
    cout << endl;

    return 0;
}

// Time Complexity:
// postTweet: O(1) - Inserting a tweet at the end of the vector
// getNewsFeed: O(N) - In the worst case, we may need to check all tweets to get 10 recent tweets
// follow: O(1) - Inserting into unordered_map
// unfollow: O(1) - Inserting into unordered_map
