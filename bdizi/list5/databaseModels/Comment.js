import database from "../database.js";


export async function getCommentById(id) {
    const [result] = await database.execute(
        "SELECT * FROM comments WHERE id = ?",
        [id]
    );
    const comment = result[0];
    return comment;
};

export async function getCommentsByBlogIdDesc(blogId) {
    const [comments] = await database.execute(
        "SELECT * FROM comments WHERE blog_id = ? ORDER BY id DESC",
        [blogId]
    );
    return comments;
};

export async function createComment(blogId, userId, body) {
    let [result] = await database.execute(
        `
        INSERT INTO
        comments (blog_id, user_id, body)
        VALUES (?, ?, ?)
        `,
        [blogId, userId, body]
    );

    const id = result.insertId;
    const newComment = getCommentById(id);
    return newComment;
};