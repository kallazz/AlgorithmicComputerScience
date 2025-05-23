const express = require('express');
const { Book } = require('../models/Book');
const { Review} = require('../models/Review');
const authMiddleware = require('../middleware/auth');
const router = express.Router();

// Dodawanie recenzji
router.post('/', authMiddleware, async (req, res) => {
  try {
    const { book_id, rating, comment } = req.body;
    
    if (!book_id || rating == null) {
      return res.status(400).json({ error: 'ID książki i ocena są wymagane' });
    }

    if (rating < 1 || rating > 5) {
      return res.status(400).json({ error: 'Ocena musi być między 1 a 5' });
    }

    const book = await Book.findById(book_id);
    if (!book) {
      return res.status(404).json({ error: 'Książka nieznaleziona' });
    }

    const review = new Review({
      user_id: req.user._id,
      book_id,
      rating,
      comment
    });

    await review.save();
    res.status(201).json(review);
  } catch (error) {
    if (error.code === 11000) {
      res.status(409).json({ error: 'Już dodałeś recenzję tej książki' });
    } else {
      res.status(500).json({ error: 'Błąd serwera' });
      console.log(error)
    }
  }
});

// Pobieranie recenzji książki
router.get('/', async (req, res) => {
  try {
    const { book_id } = req.query;
    
    let filter = {};
    if (book_id) {
      filter.book_id = book_id;
    }

    const reviews = await Review.find(filter)
      .populate('user_id', 'username')
      .populate('book_id', 'title')
      .sort({ createdAt: -1 });

    const formattedReviews = reviews.map(review => ({
      ...review.toObject(),
      username: review.user_id?.username,
      book_title: review.book_id?.title
    }));

    res.json(formattedReviews);
  } catch (error) {
    res.status(500).json({ error: 'Błąd serwera' });
  }
});

// Pobieranie pojedynczej recenzji
router.get('/:id', async (req, res) => {
  try {
    const { id } = req.params;
    const review = await Review.findById(id)
      .populate('user_id', 'username')
      .populate('book_id', 'title');
    
    if (!review) {
      return res.status(404).json({ error: 'Recenzja nieznaleziona' });
    }

    const formattedReview = {
      ...review.toObject(),
      username: review.user_id?.username,
      book_title: review.book_id?.title
    };

    res.json(formattedReview);
  } catch (error) {
    res.status(500).json({ error: 'Błąd serwera' });
  }
});

// Aktualizacja recenzji
router.put('/:id', authMiddleware, async (req, res) => {
  try {
    const { id } = req.params;
    const { rating, comment } = req.body;

    const review = await Review.findById(id);
    if (!review) {
      return res.status(404).json({ error: 'Recenzja nieznaleziona' });
    }

    if (req.user.role !== 'admin' && review.user_id.toString() !== req.user._id.toString()) {
      return res.status(403).json({ error: 'Brak uprawnień' });
    }

    if (rating && (rating < 1 || rating > 5)) {
      return res.status(400).json({ error: 'Ocena musi być między 1 a 5' });
    }

    const updatedReview = await Review.findByIdAndUpdate(
      id,
      { rating, comment },
      { new: true }
    );

    res.json(updatedReview);
  } catch (error) {
    res.status(500).json({ error: 'Błąd serwera' });
  }
});

// Usuwanie recenzji
router.delete('/:id', authMiddleware, async (req, res) => {
  try {
    const { id } = req.params;

    const review = await Review.findById(id);
    if (!review) {
      return res.status(404).json({ error: 'Recenzja nieznaleziona' });
    }

    if (req.user.role !== 'admin' && review.user_id.toString() !== req.user._id.toString()) {
      return res.status(403).json({ error: 'Brak uprawnień' });
    }

    await Review.findByIdAndDelete(id);
    res.status(204).send();
  } catch (error) {
    res.status(500).json({ error: 'Błąd serwera' });
  }
});

module.exports = router;