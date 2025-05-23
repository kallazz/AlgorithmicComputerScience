const mongoose = require('mongoose');

const reviewSchema = new mongoose.Schema({
  user_id: { type: mongoose.Schema.Types.ObjectId, ref: 'User', required: true },
  book_id: { type: mongoose.Schema.Types.ObjectId, ref: 'Book', required: true },
  rating: { type: Number, required: true, min: 1, max: 5 },
  comment: String
}, { timestamps: true });

reviewSchema.index({ user_id: 1, book_id: 1 }, { unique: true });

module.exports = {
  Review: mongoose.model('Review', reviewSchema)
};