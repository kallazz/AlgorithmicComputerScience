const createApp = require('./app');

const PORT = process.env.PORT || 3000;

createApp().then((app) => {
  app.listen(PORT, () => {
    console.log(`Serwer działa na porcie ${PORT}`);
  });
});
