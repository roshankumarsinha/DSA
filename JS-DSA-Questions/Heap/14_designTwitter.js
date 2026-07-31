// Design Twitter (simplified).

// Support:
// 1. postTweet(userId, tweetId) — compose a new tweet.
// 2. getNewsFeed(userId) — 10 most recent tweet IDs from the user and the people they follow,
//    most recent first.
// 3. follow(followerId, followeeId)
// 4. unfollow(followerId, followeeId)

// Video Explanation : https://www.youtube.com/watch?v=iV_8CTkwA1o

// Approach (map + array):
// - followers: Map(followerId -> Set of followeeIds).
// - tweets: array of [tweetId, userId] in post order (most recent at the end).
// - getNewsFeed: scan tweets from the end, collecting tweets by the user or those they follow,
//   up to 10.

// JavaScript note: C++ used unordered_map<int, unordered_map<int,int>> (0/1 for follow state).
// A Map of Sets is the cleaner JS equivalent — membership in the Set means "followed".
class Twitter {
  constructor() {
    this.followers = new Map(); // followerId -> Set(followeeId)
    this.tweets = []; // [tweetId, userId], most recent at the end
  }

  postTweet(userId, tweetId) {
    this.tweets.push([tweetId, userId]);
  }

  getNewsFeed(userId) {
    const newsFeed = [];
    const followees = this.followers.get(userId) || new Set();

    for (let i = this.tweets.length - 1; i >= 0 && newsFeed.length < 10; i--) {
      const [tweetId, tweetUserId] = this.tweets[i];
      if (tweetUserId === userId || followees.has(tweetUserId)) {
        newsFeed.push(tweetId);
      }
    }
    return newsFeed;
  }

  follow(followerId, followeeId) {
    if (!this.followers.has(followerId)) {
      this.followers.set(followerId, new Set());
    }
    this.followers.get(followerId).add(followeeId);
  }

  unfollow(followerId, followeeId) {
    if (this.followers.has(followerId)) {
      this.followers.get(followerId).delete(followeeId);
    }
  }
}

// Driver code
const twitter = new Twitter();
twitter.postTweet(1, 5);
console.log(twitter.getNewsFeed(1)); // [5]
twitter.follow(1, 2);
twitter.postTweet(2, 6);
console.log(twitter.getNewsFeed(1)); // [6, 5]
twitter.unfollow(1, 2);
console.log(twitter.getNewsFeed(1)); // [5]

// Time Complexity: postTweet O(1), getNewsFeed O(N), follow/unfollow O(1).
