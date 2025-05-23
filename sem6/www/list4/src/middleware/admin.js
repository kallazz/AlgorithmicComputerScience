const adminMiddleware = (req, res, next) => {
  if (req.user.role !== 'admin') {
    return res.status(403).json({ error: 'Brak uprawnień administratora' });
  }
  next();
};

module.exports = adminMiddleware;