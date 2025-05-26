const request = require('supertest');
const { Book } = require('../src/models/Book');
const { Review } = require('../src/models/Review');

describe('Reviews Routes', () => {
  let admin, user1, user2, adminToken, user1Token, user2Token, testBook;

  beforeEach(async () => {
    admin = await createTestAdmin();
    user1 = await createTestUser({ username: 'user1', email: 'user1@example.com' });
    user2 = await createTestUser({ username: 'user2', email: 'user2@example.com' });
    
    adminToken = generateAuthToken(admin._id);
    user1Token = generateAuthToken(user1._id);
    user2Token = generateAuthToken(user2._id);

    testBook = await new Book({
      title: 'Test Book',
      author: 'Test Author',
      isbn: '978-3-16-148410-0'
    }).save();
  });

  describe('POST /api/reviews - Add Review', () => {
    it('should allow authenticated user to add review', async () => {
      const reviewData = {
        book_id: testBook._id,
        rating: 4,
        comment: 'Great book!'
      };

      const response = await request(app)
        .post('/api/reviews')
        .set('Authorization', `Bearer ${user1Token}`)
        .send(reviewData);

      expect(response.status).toBe(201);
      expect(response.body.book_id).toBe(testBook._id.toString());
      expect(response.body.rating).toBe(4);
      expect(response.body.comment).toBe('Great book!');
    });

    it('should reject unauthenticated review', async () => {
      const response = await request(app)
        .post('/api/reviews')
        .send({
          book_id: testBook._id,
          rating: 4,
          comment: 'Great book!'
        });

      expect(response.status).toBe(401);
    });

    it('should reject review without required fields', async () => {
      const response = await request(app)
        .post('/api/reviews')
        .set('Authorization', `Bearer ${user1Token}`)
        .send({
          comment: 'Missing book_id and rating'
        });

      expect(response.status).toBe(400);
      expect(response.body.error).toBe('ID książki i ocena są wymagane');
    });

    it('should reject invalid rating values', async () => {
      const invalidRatings = [-1, 0, 6, 10];

      for (const rating of invalidRatings) {
        const response = await request(app)
          .post('/api/reviews')
          .set('Authorization', `Bearer ${user1Token}`)
          .send({
            book_id: testBook._id,
            rating: rating,
            comment: 'Test comment'
          });

        expect(response.status).toBe(400);
        expect(response.body.error).toBe('Ocena musi być między 1 a 5');
      }
    });

    it('should reject review for non-existent book', async () => {
      const nonExistentBookId = '507f1f77bcf86cd799439011';
      const response = await request(app)
        .post('/api/reviews')
        .set('Authorization', `Bearer ${user1Token}`)
        .send({
          book_id: nonExistentBookId,
          rating: 4,
          comment: 'Review for non-existent book'
        });

      expect(response.status).toBe(404);
      expect(response.body.error).toBe('Książka nieznaleziona');
    });

    it('should reject duplicate review from same user', async () => {
      await request(app)
        .post('/api/reviews')
        .set('Authorization', `Bearer ${user1Token}`)
        .send({
          book_id: testBook._id,
          rating: 4,
          comment: 'First review'
        });

      const response = await request(app)
        .post('/api/reviews')
        .set('Authorization', `Bearer ${user1Token}`)
        .send({
          book_id: testBook._id,
          rating: 5,
          comment: 'Second review'
        });

      expect(response.status).toBe(409);
      expect(response.body.error).toBe('Już dodałeś recenzję tej książki');
    });

    it('should allow different users to review same book', async () => {
      await request(app)
        .post('/api/reviews')
        .set('Authorization', `Bearer ${user1Token}`)
        .send({
          book_id: testBook._id,
          rating: 4,
          comment: 'User1 review'
        });

      const response = await request(app)
        .post('/api/reviews')
        .set('Authorization', `Bearer ${user2Token}`)
        .send({
          book_id: testBook._id,
          rating: 5,
          comment: 'User2 review'
        });

      expect(response.status).toBe(201);
    });
  });

  describe('GET /api/reviews - List Reviews', () => {
    let book2, review1, review2, review3;

    beforeEach(async () => {
      book2 = await new Book({
        title: 'Second Book',
        author: 'Second Author',
        isbn: '978-3-16-148410-1'
      }).save();

      review1 = await new Review({
        user_id: user1._id,
        book_id: testBook._id,
        rating: 4,
        comment: 'Good book'
      }).save();

      review2 = await new Review({
        user_id: user2._id,
        book_id: testBook._id,
        rating: 5,
        comment: 'Excellent book'
      }).save();

      review3 = await new Review({
        user_id: user1._id,
        book_id: book2._id,
        rating: 3,
        comment: 'Average book'
      }).save();
    });

    it('should return all reviews without authentication', async () => {
      const response = await request(app)
        .get('/api/reviews');

      expect(response.status).toBe(200);
      expect(Array.isArray(response.body)).toBe(true);
      expect(response.body).toHaveLength(3);
      
      const dates = response.body.map(review => new Date(review.createdAt));
      for (let i = 1; i < dates.length; i++) {
        expect(dates[i-1].getTime()).toBeGreaterThanOrEqual(dates[i].getTime());
      }
    });

    it('should filter reviews by book_id', async () => {
      const response = await request(app)
        .get(`/api/reviews?book_id=${testBook._id}`);

      expect(response.status).toBe(200);
      expect(response.body).toHaveLength(2);
      expect(response.body.every(review => review.book_id._id === testBook._id.toString())).toBe(true);
    });

    it('should populate user and book data', async () => {
      const response = await request(app)
        .get('/api/reviews');

      expect(response.status).toBe(200);
      expect(response.body[0]).toHaveProperty('username');
      expect(response.body[0]).toHaveProperty('book_title');
      expect(response.body[0].username).toBeDefined();
      expect(response.body[0].book_title).toBeDefined();
    });

    it('should handle empty results', async () => {
      const nonExistentBookId = '507f1f77bcf86cd799439011';
      const response = await request(app)
        .get(`/api/reviews?book_id=${nonExistentBookId}`);

      expect(response.status).toBe(200);
      expect(response.body).toHaveLength(0);
    });
  });

  describe('GET /api/reviews/:id - Get Single Review', () => {
    let testReview;

    beforeEach(async () => {
      testReview = await new Review({
        user_id: user1._id,
        book_id: testBook._id,
        rating: 4,
        comment: 'Test review'
      }).save();
    });

    it('should return single review with populated data', async () => {
      const response = await request(app)
        .get(`/api/reviews/${testReview._id}`);

      expect(response.status).toBe(200);
      expect(response.body._id).toBe(testReview._id.toString());
      expect(response.body.rating).toBe(4);
      expect(response.body.comment).toBe('Test review');
      expect(response.body).toHaveProperty('username');
      expect(response.body).toHaveProperty('book_title');
    });

    it('should return 404 for non-existent review', async () => {
      const nonExistentId = '507f1f77bcf86cd799439011';
      const response = await request(app)
        .get(`/api/reviews/${nonExistentId}`);

      expect(response.status).toBe(404);
      expect(response.body.error).toBe('Recenzja nieznaleziona');
    });
  });

  describe('PUT /api/reviews/:id - Update Review', () => {
    let testReview;

    beforeEach(async () => {
      testReview = await new Review({
        user_id: user1._id,
        book_id: testBook._id,
        rating: 4,
        comment: 'Original comment'
      }).save();
    });

    it('should allow author to update own review', async () => {
      const updateData = {
        rating: 5,
        comment: 'Updated comment'
      };

      const response = await request(app)
        .put(`/api/reviews/${testReview._id}`)
        .set('Authorization', `Bearer ${user1Token}`)
        .send(updateData);

      expect(response.status).toBe(200);
      expect(response.body.rating).toBe(5);
      expect(response.body.comment).toBe('Updated comment');
    });

    it('should allow admin to update any review', async () => {
      const updateData = {
        rating: 2,
        comment: 'Admin updated comment'
      };

      const response = await request(app)
        .put(`/api/reviews/${testReview._id}`)
        .set('Authorization', `Bearer ${adminToken}`)
        .send(updateData);

      expect(response.status).toBe(200);
      expect(response.body.rating).toBe(2);
      expect(response.body.comment).toBe('Admin updated comment');
    });

    it('should reject update by different user', async () => {
      const response = await request(app)
        .put(`/api/reviews/${testReview._id}`)
        .set('Authorization', `Bearer ${user2Token}`)
        .send({
          rating: 1,
          comment: 'Hacked comment'
        });

      expect(response.status).toBe(403);
      expect(response.body.error).toBe('Brak uprawnień');
    });

    it('should reject invalid rating in update', async () => {
      const response = await request(app)
        .put(`/api/reviews/${testReview._id}`)
        .set('Authorization', `Bearer ${user1Token}`)
        .send({
          rating: 6,
          comment: 'Updated comment'
        });

      expect(response.status).toBe(400);
      expect(response.body.error).toBe('Ocena musi być między 1 a 5');
    });

    it('should return 404 for non-existent review', async () => {
      const nonExistentId = '507f1f77bcf86cd799439011';
      const response = await request(app)
        .put(`/api/reviews/${nonExistentId}`)
        .set('Authorization', `Bearer ${user1Token}`)
        .send({
          rating: 5,
          comment: 'Updated comment'
        });

      expect(response.status).toBe(404);
      expect(response.body.error).toBe('Recenzja nieznaleziona');
    });

    it('should reject unauthenticated update', async () => {
      const response = await request(app)
        .put(`/api/reviews/${testReview._id}`)
        .send({
          rating: 5,
          comment: 'Unauthenticated update'
        });

      expect(response.status).toBe(401);
    });
  });

  describe('DELETE /api/reviews/:id - Delete Review', () => {
    let testReview;

    beforeEach(async () => {
      testReview = await new Review({
        user_id: user1._id,
        book_id: testBook._id,
        rating: 4,
        comment: 'Review to delete'
      }).save();
    });

    it('should allow author to delete own review', async () => {
      const response = await request(app)
        .delete(`/api/reviews/${testReview._id}`)
        .set('Authorization', `Bearer ${user1Token}`);

      expect(response.status).toBe(204);

      const deletedReview = await Review.findById(testReview._id);
      expect(deletedReview).toBeNull();
    });

    it('should allow admin to delete any review', async () => {
      const response = await request(app)
        .delete(`/api/reviews/${testReview._id}`)
        .set('Authorization', `Bearer ${adminToken}`);

      expect(response.status).toBe(204);

      const deletedReview = await Review.findById(testReview._id);
      expect(deletedReview).toBeNull();
    });

    it('should reject deletion by different user', async () => {
      const response = await request(app)
        .delete(`/api/reviews/${testReview._id}`)
        .set('Authorization', `Bearer ${user2Token}`);

      expect(response.status).toBe(403);
      expect(response.body.error).toBe('Brak uprawnień');
    });

    it('should return 404 for non-existent review', async () => {
      const nonExistentId = '507f1f77bcf86cd799439011';
      const response = await request(app)
        .delete(`/api/reviews/${nonExistentId}`)
        .set('Authorization', `Bearer ${user1Token}`);

      expect(response.status).toBe(404);
      expect(response.body.error).toBe('Recenzja nieznaleziona');
    });

    it('should reject unauthenticated deletion', async () => {
      const response = await request(app)
        .delete(`/api/reviews/${testReview._id}`);

      expect(response.status).toBe(401);
    });
  });

  describe('Edge Cases and Error Handling', () => {
    it('should handle malformed ObjectIds gracefully', async () => {
      const response = await request(app)
        .get('/api/reviews/invalid-object-id');

      expect(response.status).toBe(500);
      expect(response.body.error).toBe('Błąd serwera');
    });

    it('should validate rating bounds strictly', async () => {
      const borderCases = [
        { rating: 0.9, shouldFail: true },
        { rating: 1, shouldFail: false },
        { rating: 1.5, shouldFail: false },
        { rating: 5, shouldFail: false },
        { rating: 5.1, shouldFail: true }
      ];

      for (const testCase of borderCases) {
        const response = await request(app)
          .post('/api/reviews')
          .set('Authorization', `Bearer ${user1Token}`)
          .send({
            book_id: testBook._id,
            rating: testCase.rating,
            comment: `Rating test: ${testCase.rating}`
          });

        if (testCase.shouldFail) {
          expect(response.status).toBe(400);
        } else {
          expect(response.status).toBe(201);
          await Review.findOneAndDelete({ user_id: user1._id, book_id: testBook._id });
        }
      }
    });
  });
});