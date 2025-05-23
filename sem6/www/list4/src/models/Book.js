const mongoose = require('mongoose');

const bookSchema = new mongoose.Schema({
  title: { type: String, required: true },
  author: { type: String, required: true },
  isbn: { type: String, required: true, unique: true },
  description: String,
  published_year: Number
}, { timestamps: true });

module.exports = {
  Book: mongoose.model('Book', bookSchema)
};